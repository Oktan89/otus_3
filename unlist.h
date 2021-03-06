#pragma once
#include <memory>
#include "myalocator.h"

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
        public:
           // using iter = typename otus::unlist<T, Allocator>::Iterator;
        private:
            Node* _it;
        public:
            Iterator() : _it(nullptr) {}
            Iterator(Node* it) : _it(it) {}
            Iterator(const Node &it) : _it(it){}
            Iterator& operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& rhs) const noexcept;
            bool operator!=(const Iterator& rhs) const noexcept;
            T& operator*();
            const T& operator*() const;
        };

    public:
        using value_type = T;
        using allocator_type = Allocator;
        using pointer = T *;
        using size_type = std::size_t;
        //using _node_alloc_type = typename Allocator::rebind<Node>::other;
        using _node_alloc_type = typename std::allocator_traits<Allocator>:: template rebind_alloc<Node>;
        using iterator = typename unlist<T, Allocator>::Iterator;
        //using const_iterator = typename unlist<T, Allocator>::Iterator;
    private:
        _node_alloc_type _alloc;
        Node *_front = nullptr;
        Node *_end = nullptr;
        size_type _count = 0;
        
    public:
        unlist() = default;

        unlist(const unlist& other);

        unlist(unlist&& other);

        unlist& operator=(const unlist& other);

        unlist& operator=(unlist&& other);
        
        bool push_back(const T& value);

        bool push_front(const T& value);

        bool pop_front();

        void clear();

        size_type size() const noexcept {return _count;}

        std::size_t max_size() const noexcept {return _alloc.max_size();}

        [[nodiscard]] bool empty() const noexcept { return _front == _end;}

        iterator begin() const noexcept;    

        iterator end() const noexcept;

        ~unlist();
    private:
       

    };

    
    template <typename T, typename Allocator>
    T& unlist<T, Allocator>::iterator::operator*()
    {
        return _it->date;
    }

    template <typename T, typename Allocator>
    const T& unlist<T, Allocator>::iterator::operator*() const
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
    bool unlist<T, Allocator>::iterator::operator==(const Iterator& rhs) const noexcept
    {
        return _it == rhs._it;
    }

    template <typename T, typename Allocator>
    bool unlist<T, Allocator>::iterator::operator!=(const Iterator& rhs) const noexcept
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
    unlist<T, Allocator>::unlist(unlist&& other)
    {   

        *this = std::move(other);
// Notes
// After container move construction (overload (8)), references, pointers, and iterators (other than the end iterator) to other remain valid, but refer to elements that are now in *this. The current standard makes this guarantee via the blanket statement in [container.requirements.general]/12, and a more direct guarantee is under consideration via LWG 2321.
    }

    template <typename T, typename Allocator>
    unlist<T, Allocator>& unlist<T, Allocator>::operator=(unlist&& other)
    {   
       if(this == &other)
             return *this;
        _front = other._front;
        _end = other._end;
        _count = other._count;
        _alloc = other._alloc;

         other._front = nullptr;
         other._end = nullptr;
         other._count = 0;
            
        return *this;
    }

     template <typename T, typename Allocator>
    unlist<T, Allocator>& unlist<T, Allocator>::operator=(const unlist& other)
    {   
        if(this == &other)
             return *this;

        Node *temp;

        while (_front != nullptr)
        {
            temp = _front;
            _front = _front->next;
            _alloc.destroy(temp);
            _alloc.deallocate(temp, 1);
        }

       for(auto &it : other)
            push_back(it);

        return *this;
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
    void unlist<T, Allocator>::clear()
    {
        Node *temp;

        while (_front != nullptr)
        {
            temp = _front;
            _front = _front->next;
            _alloc.destroy(temp);
            _alloc.deallocate(temp, 1);
        }
        _end = nullptr;
        _count = 0;
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
    bool unlist<T, Allocator>::pop_front()
    {
        if(_front == nullptr)
            return false;
        --_count;
        Node* temp;
        temp = _front;
        _front = _front->next;
        _alloc.destroy(temp);
        _alloc.deallocate(temp, 1);
        
        if(_count == 0)
            _end = nullptr;
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
