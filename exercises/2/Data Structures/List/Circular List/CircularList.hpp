#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace dsa
{
template <class T>
class CircularList
{
private:
    struct Node;

public:
    CircularList();
    CircularList( const CircularList<T>& );
    CircularList<T>& operator=( const CircularList<T>& );
    ~CircularList();

public:
    class iterator
    {
        friend CircularList;
    public:
        typedef iterator        self_type;
        typedef T               value_type;
        typedef T&              reference;
        typedef const T&        const_reference;
        typedef T*              pointer;
        typedef int             difference_type;

        iterator( Node* ptr = nullptr ) : m_node_ptr( ptr ) {}
    public:
        /* access operators */
        reference       operator*()         { return m_node_ptr->data; }
        const_reference operator*() const   { return m_node_ptr->data; }
        pointer         operator->()        { return m_node_ptr;  }

        /* compare operators */
        bool operator==(const self_type& rhs) const { return m_node_ptr == rhs.m_node_ptr; }
        bool operator!=(const self_type& rhs) const { return !(rhs == *this); }

        /* modifier operators */
        self_type& operator++();        // prefix ++
        self_type operator++( int );    // postfix ++

    private:
        operator        Node*()         { return m_node_ptr; }
        operator const  Node*() const   { return m_node_ptr; }

    private:
        Node* m_node_ptr;
    };

public:
    void            push_front( const T& element);
    void            push_back( const T& element);
    void            pop_front();

    iterator        insertAfter( const iterator& it, const T& element);
    iterator        removeAfter( const iterator& it );

    iterator        begin()     const   { return iterator( head ); }
    iterator        end()       const   { return this->begin();    }

    inline T&       front()             { return head->data; }
    inline const T& front()     const   { return head->data; }

    inline size_t   getSize()   const   { return size;      }
    inline bool     isEmpty()   const   { return size == 0; }

    void            print()     const;

private:
    void copy( const CircularList<T>& other);
    void clean();

private:
    struct Node
    {
        Node* pNext;
        T data;

        Node( const T& data, Node* nextNode = nullptr ) : data( data ), pNext( nextNode ) {}
    };

private:
    Node* head;
    Node* tail;
    size_t size;
};

} // end namespace dsa

#include "CircularList.ipp"
