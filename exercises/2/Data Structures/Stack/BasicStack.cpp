// Very basic example of a stack

#include <iostream>


const size_t    CAPACITY            = 128;
size_t          size                = 0;
int             stack[ CAPACITY ]   = { 0, };


void push( int elem )
{
    stack[ size++ ] = elem;
}


void pop()
{
    if ( size > 0 )
    {
        --size;
    }
}


int& top()
{
    return stack[ size - 1 ];
}


bool empty()
{
    return size == 0;
}


int main()
{

    for ( size_t i = 1; i <= 32; i++ )
    {
        push( i );
    }

    while ( !empty() )
    {
        std::cout << top() << "\n";
        pop();
    }

    return 0;
}
