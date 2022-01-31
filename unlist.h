#pragma once
#include <iostream>
#include <memory>


namespace otus
{

    template <typename T, typename Allocator = std::allocator<T>>
    class unlist
    {
    protected:
        struct Node
        {
            T date;
            Node *next;
        };

    public:
        using value_type = T;
        using allocator_type = Allocator;
        using pointer = T *;
        using size_type = std::size_t;
        using _node_alloc_type = typename Allocator::rebind<Node>::other;

    protected:
        _node_alloc_type _alloc;
        Node *front = nullptr;
        Node *end = nullptr;
        const size_type _size;
        size_type _count;

    public:
        explicit unlist(const Allocator &alloc = Allocator());

        bool push_front(const T &value);

        ~unlist();
    protected:
        bool isfull();
    };

    template <typename T, typename Allocator>
    unlist<T, Allocator>::unlist(const Allocator &alloc) : _alloc(alloc), _size(10), _count(0)
    {
 
    }

    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::push_front(const T &value)
    {
        if(isfull())
            return false;

        Node temp{value, nullptr};

        auto p = _alloc.allocate(1);
        _alloc.construct(p,temp);

        ++_count;

        if(front == nullptr)
        {
            front = p;
        }
        else
        {
            end->next = p;
        }

        end = p;
        return true;
    }

    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::isfull()
    {
        return (_count >= _size)? true : false;
    }

    template <typename T, typename Allocator>
    unlist<T, Allocator>::~unlist()
    {

    }
}
