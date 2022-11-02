#pragma once

namespace dsa
{

template <typename T, size_t CAPACITY>
class StaticQueue
{
public:
    StaticQueue();

    void        enqueue( const T& elem );
    T           dequeue();

    void        push( const T& elem );
    void        pop();
    T&          front();
    const T&    front() const;
    size_t      size()  const;
    bool        empty() const;

private:
    T       fData[ CAPACITY ];
    size_t  fHeadIndex;
    size_t  fTailIndex;
    size_t  fSize;
};

} // end of namespace dsa

#include "StaticQueue.ipp"
