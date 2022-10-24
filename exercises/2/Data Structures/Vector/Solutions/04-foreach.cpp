#include <iostream>
#include <vector>

template <class T, class Func>
void foreach( std::vector<T>& vec, const Func& function )
{
    for ( T& elem : vec )
        function( elem );
}

void square( int& num )
{
    num *= num;
}

void print( const std::vector<int>& vec )
{
    for ( int elem : vec )
        std::cout << elem << "\t";

    std::cout << "\n";
}

int main()
{
    std::vector<int>    vec     = { 5, 10, 12, 43, -123, -4, 3, 1 };

    print( vec );
    foreach( vec, square );
    print( vec );

    // Lambda function as an argument
    foreach( vec, [] ( int& num ) { num %= 10; } );
    print( vec );
    
    return 0;
}
