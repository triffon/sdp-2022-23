#include "StaticQueue.hpp"

namespace dsa
{

template<typename T, size_t CAPACITY>
inline StaticQueue<T, CAPACITY>::StaticQueue()
    : fHeadIndex( 0 )
    , fTailIndex( 0 )
    , fSize( 0 )
{}


template<typename T, size_t CAPACITY>
inline void StaticQueue<T, CAPACITY>::enqueue( const T& elem )
{
    if ( fSize == CAPACITY )
        throw std::logic_error( "StaticQueue: enqueue to a full queue!" );

    fData[ fTailIndex++ ] = elem;

    if ( fTailIndex >= CAPACITY )
        fTailIndex = 0;

    ++fSize;
}


template<typename T, size_t CAPACITY>
inline T StaticQueue<T, CAPACITY>::dequeue()
{
    if ( this->empty() )
        throw std::logic_error( "StaticQueue: dequeue from an empty queue!" );

    T   res = fData[ fHeadIndex++ ];

    if ( fHeadIndex >= CAPACITY )
        fHeadIndex = 0;

    --fSize;

    return res;
}


template<typename T, size_t CAPACITY>
inline void StaticQueue<T, CAPACITY>::push( const T& elem )
{
    this->enqueue( elem );
}


template<typename T, size_t CAPACITY>
inline void StaticQueue<T, CAPACITY>::pop()
{
    this->dequeue();
}


template<typename T, size_t CAPACITY>
inline T& StaticQueue<T, CAPACITY>::front()
{
    return const_cast< T& >( std::as_const( *this ).front() );
}


template<typename T, size_t CAPACITY>
inline const T& StaticQueue<T, CAPACITY>::front() const
{
    if ( this->empty() )
        throw std::logic_error( "StaticQueue: front of an empty queue!" );

    return fData[ fHeadIndex ];
}


template<typename T, size_t CAPACITY>
inline size_t StaticQueue<T, CAPACITY>::size() const
{
    return fSize;
}


template<typename T, size_t CAPACITY>
inline bool StaticQueue<T, CAPACITY>::empty() const
{
    return this->size() == 0;
}


} // end of namespace dsa
