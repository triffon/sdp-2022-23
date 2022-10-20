#pragma once

namespace dsa
{

class DynamicStack
{
public:
    DynamicStack();
    DynamicStack( const DynamicStack& other );
    DynamicStack& operator=( DynamicStack other );
    ~DynamicStack();

    bool        push( int elem );
    bool        pop();
    int&        top();
    const int&  top()   const;
    bool        empty() const;

    void        swap( DynamicStack& other );

private:
    bool resize();

private:
    int*    fData;
    size_t  fSize;
    size_t  fCapacity;
};

} // end namespace dsa
