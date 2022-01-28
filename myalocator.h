#pragma once
#include <memory>
#include <limits>

template <class T>
struct Myallocator
{
  using value_type = T;
 
  Myallocator () = default;
  template <class U> 
  constexpr Myallocator (const Myallocator <U>&) noexcept {}
 
  T* allocate(std::size_t n) {
    if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
      throw std::bad_array_new_length();
 
    if (auto p = static_cast<T*>(std::malloc(n*sizeof(T)))) {
      report(p, n);
      return p;
    }
 
    throw std::bad_alloc();
  }
 
  void deallocate(T* p, std::size_t n) noexcept {
    report(p, n, 0);
    std::free(p);
  }

  template< class U, class... Args >
  void construct( U* p, Args&&... args )
  {
    //report(p, 0, 0);
    printf("args: %d \n", args ...);
      new((void *)p) U(std::forward<Args>(args)...);
      
  }
 
private:
  void report(T* p, std::size_t n, bool alloc = true) const {
    std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T)*n
      << " bytes at " << std::hex << std::showbase
      << reinterpret_cast<void*>(p) << std::dec << '\n';
  }
};
 
template <class T, class U>
bool operator==(const Myallocator <T>&, const Myallocator <U>&) { return true; }
template <class T, class U>
bool operator!=(const Myallocator <T>&, const Myallocator <U>&) { return false; }





