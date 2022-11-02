#include "CircularList.hpp"

namespace dsa
{


template<class T>
CircularList<T>::CircularList() 
    : head( nullptr )
    , tail( nullptr )
    , size( 0 )
{}


template<class T>
CircularList<T>::CircularList( const CircularList<T>& other )
    : CircularList()
{
    this->copy( other );
}


template<class T>
CircularList<T>& CircularList<T>::operator=( const CircularList<T>& other )
{
    if ( this != &other )
    {
        this->clean();
        this->copy( other );
    }
    return *this;
}


template<class T>
CircularList<T>::~CircularList()
{
    this->clean();
}


template<class T>
void CircularList<T>::copy( const CircularList<T>& other )
{
    if ( other.isEmpty() )
    {
        return;
    }

    try
    {
        head = new Node( other.head->data );
        Node* toCopy = other.head;
        Node* copied = head;
        size++;

        while ( toCopy->pNext != other.head )
        {
            toCopy = toCopy->pNext;

            copied->pNext = new Node( toCopy->data );
            copied = copied->pNext;
            size++;
        }

        tail = copied;
    }
    catch (...)
    {
        this->clean();
        throw;
    }
}


template<class T>
void CircularList<T>::clean()
{
    while ( !this->isEmpty() )
    {
        this->pop_front();
    }
}


template<class T>
inline typename CircularList<T>::iterator&
    CircularList<T>::iterator::operator++()
{
    m_node_ptr = m_node_ptr->pNext;
    return *this;
}


template<class T>
inline typename CircularList<T>::iterator
    CircularList<T>::iterator::operator++( int )
{ 
    self_type res(*this);
    ++(*this);
    return res;
}


template<class T>
void CircularList<T>::print() const
{
    Node* ptr = head;
    if ( head )
    {
        do
        {
            std::cout << ptr->data << ' ';
            ptr = ptr->pNext;
        }
        while ( ptr != head );
    }
    std::cout << std::endl;
}


template<class T>
void CircularList<T>::push_front( const T& newData )
{
    head = new Node( newData, head );
    if ( size == 0 )
    {
        tail = head;
    }
    ++size;

    tail->pNext = head;
}


template<class T>
inline void CircularList<T>::push_back( const T& element )
{
    if ( size == 0 )
    {
        this->push_front( element );
    }
    else
    {
        tail->pNext = new Node( element, head );
        tail        = tail->pNext;
        ++size;
    }
}


template<class T>
void CircularList<T>::pop_front()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }
    Node* temp = head;
    head = head->pNext;
    delete temp;
    --size;
    if ( size == 0 )
    {
        tail = nullptr;
        head = nullptr;
    }
    else
    {
        tail->pNext = head;
    }
}


template<class T>
typename CircularList<T>::iterator CircularList<T>::insertAfter( const iterator& it, const T& newData )
{
    Node* new_node = new Node( newData, it.m_node_ptr->pNext );

    it.m_node_ptr->pNext = new_node;

    ++size;
    return new_node;
}


template<class T>
typename CircularList<T>::iterator CircularList<T>::removeAfter( const iterator& it )
{
    if ( this->isEmpty() )
    {
        throw std::logic_error( "empty forward list!" );
    }
    if ( size == 1 )
    {
        delete it.m_node_ptr;
        return nullptr;
    }
    Node* removed = it.m_node_ptr->pNext;
    if ( removed == tail )
    {
        tail = it.m_node_ptr;
    }
    if ( removed == head )
    {
        head = head->pNext;
    }
    it.m_node_ptr->pNext = removed->pNext;

    delete removed;

    --size;
    if ( size == 1 )
    {
        return head ? head : tail;
    }
    return it.m_node_ptr->pNext;
}


}
