#pragma once
#include <memory>
#include <typeinfo>
#include <limits>
#include <cassert>

#define _LOG_ 0

//1 param T - object
//2 param set_size - sets the number of objects to be placed on the stack
namespace otus
{

  template <class T, int set_size = 500>
  class Myallocator
  {
  public:     
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
  
    char buff[set_size * sizeof(T)];
    char buff_2[sizeof(buff)];

    size_type _max_size = sizeof(buff) / sizeof(value_type);
    size_type _courent_obg_T = 0;
    char* begin = buff;
    char* current = begin;
    char* end = begin + sizeof(buff)-sizeof(value_type);

    char* begin_2 = buff_2;
    char* current_2 = begin_2;
    char* end_2 = begin_2 + sizeof(buff_2)-sizeof(value_type);

    bool switch_mem = true;
  public:

    template <typename U, int copy_byte = set_size>
    struct rebind
    {
      using other = Myallocator<U, copy_byte>;
    };

    Myallocator() {initmem();}
    ~Myallocator() = default;

    template <class U, int copy_byte = set_size>
    constexpr Myallocator(const Myallocator<U, copy_byte> &) noexcept {}

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
      if(n > _max_size || _courent_obg_T >=_max_size)
        throw std::runtime_error("bad_allocate memory: request (" + std::to_string(_courent_obg_T+1) +") (size " + std::to_string(n) + "). Allocated object size " 
          + std::to_string(_courent_obg_T) +", max size: " + std::to_string(_max_size)  + 
          " \'try increasing the set_size parameter allocator");
  
      pointer p;
      if(switch_mem)
      {
          p = reinterpret_cast<pointer>(current);
          p = setmem(p, end, n);
          if(p == nullptr)
            throw std::bad_alloc();
          current +=sizeof(value_type)*n;
          switch_mem = false;
      }
      else
      {
          p = reinterpret_cast<pointer>(current_2);
          p = setmem(p, end_2, n);
          if(p == nullptr)
            throw std::bad_alloc();
          current_2 +=sizeof(value_type)*n;
          switch_mem = true;
      }
  #if _LOG_
      report(p, n);
  #endif
      if(current_2 > end_2 + sizeof(value_type) || current > end + sizeof(value_type))
        throw std::bad_alloc();
      _courent_obg_T += n;    
      return p;

    }
private:
    void initmem() noexcept
    { 
      for(std::size_t i = 0; i < sizeof(buff); ++i)
      {
        buff[i] = '\n';
        buff_2[i] = '\n';
      }
    }
    pointer setmemObj(pointer p,size_type n)
    {
        char *__p = reinterpret_cast<char *>(p);
        bool memused = false;
        for (std::size_t i = 0; i < n * sizeof(value_type); ++i)
        {
          if (*__p != '\n')
          {
            memused = true;
            break;
          }
          else ++__p;
        }
      return (memused)? nullptr : p;
    }

    pointer setmem(pointer p, char* end, size_type n)
    {
        while(reinterpret_cast<char *>(p) < end + sizeof(value_type))
        {
          if(nullptr == setmemObj(p, n))
            ++p;
          else return p;
        }
        return nullptr;
    }
public:
    void deallocate([[maybe_unused]] pointer p, [[maybe_unused]] size_type n) noexcept
    {
  #if _LOG_
      report(p, n, 0);
  #endif
      [[maybe_unused]] char* __p = reinterpret_cast<char*>(p);
      for(std::size_t i =0; i < n * sizeof(value_type); ++i)
      {
          [[maybe_unused]] char* temp = __p;
          __p++;
          *temp = '\n';     
      }
      
      (switch_mem)? current = begin : current_2 = begin_2;
      _courent_obg_T -= n;
    }

    template <class U, class... Args>
    void construct(U *p, Args &&...args)
    {
  #if _LOG_
      std::cout << "construct: " << typeid(p).name() << '\n';
  #endif
      new ((void *)p) U(std::forward<Args>(args)...);

    }

    template< class U >
    void destroy( U *p )
    {
  #if _LOG_
      std::cout << "destroy: " << typeid(p).name() << '\n';
  #endif
      p->~U();
    }

    value_type max_size()
    {
      return _max_size;
    }

  private:
    
  #if _LOG_
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

}