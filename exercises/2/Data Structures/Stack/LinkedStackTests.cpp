#include <iostream>
#include "LinkedStack.hpp"

int main()
{
    dsa::LinkedStack    stack1, stack2;

    stack2.push( 5 );
    stack2.push( 10 );
    stack2.push( 15 );

    for ( size_t i = 1; i <= 32; i++ )
    {
        stack1.push( i );
    }

    stack2  = stack1;

    while ( !stack2.empty() )
    {
        std::cout << stack2.top() << "\n";
        stack2.pop();
    }

    return 0;
}
