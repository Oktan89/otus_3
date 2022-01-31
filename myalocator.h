#pragma once
#include <memory>
#include <typeinfo>
#include <limits>

#define _LOG_ 
#define UNUSED(x) (void)(x)

//2 param set_byte - set count byte for all object to be placed on the stack
template <class T, int set_byte = 500>
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
 
  char buff[set_byte];
  char buff_2[sizeof(buff)];
  size_type _max_size = sizeof(buff) / sizeof(value_type);
  char* begin = buff;
  char* current = begin;
  char* end = begin + sizeof(buff);

  char* begin_2 = buff_2;
  char* current_2 = begin_2;
  char* end_2 = begin_2 + sizeof(buff_2);

  bool switch_mem = true;
public:

  template <typename U, int copy_byte = set_byte>
  struct rebind
  {
    using other = Myallocator<U, copy_byte>;
  };

  Myallocator() = default;
  ~Myallocator() = default;

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
    if(n > _max_size)
      throw std::runtime_error("bad_allocate size " + std::to_string(n) +", max size: " + std::to_string(_max_size)  + 
        " \'try increasing the byte_set parameter allocator \'");

    pointer p;
    if(switch_mem)
    {
        p = reinterpret_cast<pointer>(current);
        current +=sizeof(value_type)*n;
        switch_mem = false;
    }
    else
    {
        p = reinterpret_cast<pointer>(current_2);
        current_2 +=sizeof(value_type)*n;
        switch_mem = true;
    }
#if defined _LOG_
    report(p, n);
#endif
    if(current_2 > end_2 || current > end)
      throw std::bad_alloc();
        
    return p;

  }

  void deallocate(pointer p, size_type n) noexcept
  {
#if defined _LOG_
    report(p, n, 0);
#else
    UNUSED(p);
    UNUSED(n);
#endif
    p = nullptr;
    (switch_mem)? current = begin : current_2 = begin_2;

  }

  template <class U, class... Args>
  void construct(U *p, Args &&...args)
  {
#if defined _LOG_
    std::cout << "construct: " << typeid(p).name() << '\n';
#endif
    new ((void *)p) U(std::forward<Args>(args)...);
  }

  template< class U >
  void destroy( U *p )
  {
#if defined _LOG_
    std::cout << "destroy: " << typeid(p).name() << '\n';
#endif
    p->~U();
  }

  value_type max_size()
  {
    return _max_size;
  }

private:
  
#if defined _LOG_
  void report(T *p, std::size_t n, bool alloc = true) const
  {
    std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
              << " bytes at " << std::hex << std::showbase
              << reinterpret_cast<void *>(p) << std::dec << '\n';
  }
#endif
};

template <class T, class U>
bool operator==(const Myallocator<T> &, const Myallocator<U> &) { return true; }
template <class T, class U>
bool operator!=(const Myallocator<T> &, const Myallocator<U> &) { return false; }

