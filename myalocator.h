#pragma once
#include <memory>
#include <limits>

template <class T, int s_byte = 500>
struct Myallocator
{     
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;
  using is_always_equal = std::true_type;

private:
  
  char buff[s_byte];
  size_type _size = 0;
  char* begin = nullptr;
  char* current = nullptr;
  char* end = nullptr;

public:

  template <typename U>
  struct rebind
  {
    using other = Myallocator<U>;
  };

  Myallocator()
  {
    begin = buff;
    _size = sizeof(buff) / sizeof(value_type);
    end = begin + sizeof(buff);
    current = begin;
  }

  template <class U>
  constexpr Myallocator(const Myallocator<U> &) noexcept {}

  pointer address(reference x) const 
  {
    return &x; 
  }
  const_pointer address(const_reference x) const 
  {
    return &x; 
  }

  pointer allocate(size_type n)
  {
    
    auto p = reinterpret_cast<pointer>(current);
    current +=sizeof(value_type)*n;
    report(p, n);
         
    return p;
    // if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
    //   throw std::bad_array_new_length();

    // if (auto p = static_cast<T *>(std::malloc(n * sizeof(T))))
    // {
    //   report(p, n);
    //   return p;
    // }

    // throw std::bad_alloc();
  }

  void deallocate(pointer p, size_type n) noexcept
  {
    report(p, n, 0);
    p = nullptr;
    // std::free(p);
  }

  template <class U, class... Args>
  void construct(U *p, Args &&...args)
  {
    std::cout << "construct\n";
    //  printf("args: %d \n", args ...);
    new ((void *)p) U(std::forward<Args>(args)...);
  }

  template< class U >
  void destroy( U *p )
  {
    std::cout << "destoy\n";
    p->~U();
  }

private:
  

  void report(T *p, std::size_t n, bool alloc = true) const
  {
    std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
              << " bytes at " << std::hex << std::showbase
              << reinterpret_cast<void *>(p) << std::dec << '\n';
  }
};

template <class T, class U>
bool operator==(const Myallocator<T> &, const Myallocator<U> &) { return true; }
template <class T, class U>
bool operator!=(const Myallocator<T> &, const Myallocator<U> &) { return false; }
