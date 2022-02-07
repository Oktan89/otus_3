#pragma once
#include <memory>


namespace otus
{

    template <typename T, typename Allocator = std::allocator<T>>
    class unlist
    {
    
        struct Node
        {
            T date;
            Node *next;
            Node(const T& value, Node* n) : date(value), next(n) {}
        };
        class Iterator 
        {
            Node* _it;
        public:
            Iterator() : _it(nullptr) {}
            Iterator(Node* it) : _it(it) {}
            Iterator(const Node &it) : _it(it){}
            Iterator& operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& rhs);
            bool operator!=(const Iterator& rhs);
            T& operator*();
        };

    public:
        using value_type = T;
        using allocator_type = Allocator;
        using pointer = T *;
        using size_type = std::size_t;
        using _node_alloc_type = typename Allocator::rebind<Node>::other;
        using iterator = typename unlist<T, Allocator>::Iterator;
        
    protected:
        _node_alloc_type _alloc;
        Node *_front = nullptr;
        Node *_end = nullptr;
        size_type _count = 0;
        
    public:
        unlist() = default;
        unlist(const unlist& other);
        // unlist(unlist&& other);
        // unlist& operator=(const unlist& other);
        // unlist& operator=(unlist&& other);
        
        bool push_back(const T& value);
     
        bool push_front(const T& value);

        size_type size() const noexcept {return _count;}

        [[nodiscard]] bool empty() const noexcept { return _front == _end;}

        iterator begin() const noexcept;    

        iterator end() const noexcept;

        ~unlist();

    };

    
    template <typename T, typename Allocator>
    T& unlist<T, Allocator>::iterator::operator*()
    {
        return _it->date;
    }

    template <typename T, typename Allocator> 
    typename unlist<T, Allocator>::Iterator& unlist<T, Allocator>::iterator::operator++()
    {
        _it = _it->next;
        return *this;
    }

    template <typename T, typename Allocator>
    typename unlist<T, Allocator>::Iterator unlist<T, Allocator>::iterator::operator++(int)
    {
        Iterator temp = *this;
        _it = _it->next;
        return temp;
    }

    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::iterator::operator==(const Iterator& rhs)
    {
        return _it == rhs._it;
    }

    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::iterator::operator!=(const Iterator& rhs)
    {
        return !(_it == rhs._it);
    }

    template <typename T, typename Allocator>
    unlist<T, Allocator>::unlist(const unlist& other)
    {
       for(auto &it : other)
            push_back(it);
    }

    template <typename T, typename Allocator>
    unlist<T, Allocator>::~unlist()
    {
        Node *temp;

        while (_front != nullptr)
        {
            temp = _front;
            _front = _front->next;
            _alloc.destroy(temp);
            _alloc.deallocate(temp, 1);
        }
    }
 
    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::push_back(const T& value)
    {

        auto p = _alloc.allocate(1);
        _alloc.construct(p, value, nullptr);

        ++_count;

        if(_front == nullptr)
        {
            _front = p;
        }
        else
        {
            _end->next = p;
        }

        _end = p;
        return true;
    }

    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::push_front(const T& value)
    {

        auto p = _alloc.allocate(1);
        _alloc.construct(p, value, nullptr);

        ++_count;

        if(_front == nullptr)
        {
            _end = p;
        }
        else
        {
            p->next = _front;
        }

        _front = p;
        return true;
    }

    template <typename T, typename Allocator>
    typename unlist<T, Allocator>::Iterator unlist<T, Allocator>::begin() const noexcept
    {
        return _front;
    }

    template <typename T, typename Allocator>
    typename unlist<T, Allocator>::Iterator unlist<T, Allocator>::end() const noexcept
    {
        return _end->next;
    }

}
