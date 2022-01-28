#pragma once
#include <memory>
#include <iostream>

namespace otus
{

    template <typename T, typename Allocator = std::allocator<T>>
    class unlist
    {
        using allocator_type = Allocator;
        using value_type = T;
        using pointer = T*;
        using size_type = std::size_t;

        allocator_type _alloc;
        pointer _p = nullptr;
        const size_type _size;
        size_type _count = 0;

    public:

        explicit unlist(size_type size = 10, const Allocator& alloc = allocator_type());

        void push_front(const T& value);

        ~unlist();

    };

    template <typename T, typename Allocator>
    unlist<T, Allocator>::unlist(size_type size, const Allocator& alloc) : _alloc(alloc), _size(size)
    {
       _p = _alloc.allocate(size);
        std::cout << "ulist: "<< _p << std::endl;;
    }

    template <typename T, typename Allocator>
    unlist<T, Allocator>::~unlist()
    {
        _alloc.deallocate(_p, _size);
    }

    template <typename T, typename Allocator>
    void unlist<T, Allocator>::push_front(const T& value)
    {
        _alloc.construct(_p + _count++, value);
    }
}

