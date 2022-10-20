#include "DynamicStack.hpp"
#include <iostream>

namespace dsa
{

DynamicStack::DynamicStack()
    : fData( nullptr )
    , fSize( 0 )
    , fCapacity( 0 )
{}


DynamicStack::DynamicStack( const DynamicStack & other )
    : DynamicStack()
{
    fData       = new int[ other.fCapacity ];
    fCapacity   = other.fCapacity;

    for ( size_t i = 0 ; i < other.fSize; ++i )
    {
        fData[ i ] = other.fData[ i ];
        ++fSize;
    }
}


DynamicStack& DynamicStack::operator=( DynamicStack other )
{
    this->swap( other );

    return *this;
}


DynamicStack::~DynamicStack()
{
    delete[] fData;
    fData       = nullptr;
    fSize       = 0;
    fCapacity   = 0;
}


bool DynamicStack::push( int elem )
{
    if ( fSize >= fCapacity )
    {
        if ( !resize() )
        {
            return false;
        }
    }

    fData[ fSize ] = elem;
    ++fSize;

    return true;
}


bool DynamicStack::pop()
{
    if ( fSize == 0 )
    {
        return false;
    }

    --fSize;
    return true;
}


int& DynamicStack::top()
{
    return const_cast< int& >( std::as_const( *this ).top() );
}


const int& DynamicStack::top() const
{
    if ( this->empty() )
        throw std::logic_error( "Can't return top of an empty stack!" );

    return fData[ fSize - 1 ];
}


bool DynamicStack::empty() const
{
    return fSize == 0;
}


void DynamicStack::swap( DynamicStack& other )
{
    std::swap( fData        , other.fData       );
    std::swap( fSize        , other.fSize       );
    std::swap( fCapacity    , other.fCapacity   );
}


bool DynamicStack::resize()
{
    size_t  newCapacity;

    if ( fCapacity == 0 )
    {
        newCapacity = 4;    // Default capacity
    }
    else
    {
        newCapacity = 2 * fCapacity;    // Default scaling factor
    }

    if ( !( newCapacity > fCapacity ) )
    {
        return false;
    }

    int* newData    = new ( std::nothrow ) int[ newCapacity ];
    if ( !newData )
    {
        return false;
    }

    for ( size_t i = 0; i < fCapacity; ++i )
    {
        std::swap( newData[ i ], fData[ i ] );
    }

    delete[] fData;
    fData       = newData;
    fCapacity   = newCapacity;

    return true;
}

} // end namespace dsa
