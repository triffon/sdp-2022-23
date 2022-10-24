#include <iostream>
#include <vector>

template <class T, class Pred>
std::vector<T> filter( const std::vector<T>& vec, const Pred& predicate )
{
    std::vector<T>  res;
    res.reserve( vec.size() );

    for ( const T& elem : vec )
        if ( predicate( elem ) )
            res.push_back( elem );

    res.shrink_to_fit();
    return res;
}

bool isEven( int num )
{
    return num % 2 == 0;
}

bool isLargerThan10( int num )
{
    return num > 10;
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

    std::cout << "Original:\t"; print( vec );

    std::vector<int>    evenVec = filter( vec, isEven );
    std::cout << "Even only:\t"; print( evenVec );

    std::cout << "Even > 10:\t";
    print( filter( filter( vec, isEven ), isLargerThan10 ) );
    
    return 0;
}
