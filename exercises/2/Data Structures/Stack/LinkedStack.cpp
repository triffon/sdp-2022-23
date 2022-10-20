#include "LinkedStack.hpp"
#include <iostream>

namespace dsa
{

LinkedStack::LinkedStack()
    : fTop( nullptr )
{}


LinkedStack::LinkedStack( const LinkedStack & other )
    : LinkedStack()
{
    if ( !other.empty() )
    {
        fTop    = new Node( other.fTop->fData );

        Node*   nextOther   = other.fTop->fNext;
        Node*   currThis    = fTop;

        while ( nextOther )
        {
            currThis->fNext = new Node( nextOther->fData );

            currThis        = currThis->fNext;
            nextOther       = nextOther->fNext;
        }
    }
}


LinkedStack& LinkedStack::operator=( LinkedStack other )
{
    this->swap( other );

    return *this;
}


LinkedStack::~LinkedStack()
{
    Node*   next;
    while ( !this->empty() )
    {
        next    = fTop->fNext;
        delete  fTop;
        fTop    = next;
    }
}


bool LinkedStack::push( int elem )
{
    Node* newNode   = new ( std::nothrow ) Node( elem, fTop );
    if ( !newNode )
    {
        return false;
    }

    fTop    = newNode;

    return true;
}


bool LinkedStack::pop()
{
    if ( this->empty() )
    {
        return false;
    }
    
    Node*   next = fTop->fNext;
    delete  fTop;
    fTop    = next;
    
    return true;
}


int& LinkedStack::top()
{
    return const_cast< int& >( std::as_const( *this ).top() );
}


const int& LinkedStack::top() const
{
    if ( this->empty() )
        throw std::logic_error( "LinkedStack: Can't return top of an empty stack!" );

    return fTop->fData;
}


bool LinkedStack::empty() const
{
    return fTop == nullptr;
}


void LinkedStack::swap( LinkedStack& other )
{
    std::swap( fTop, other.fTop );
}

} // end namespace dsa
