#include <iostream>
#include <vector>

// Finding an element in a vector, returning a pointer to it, or nullptr
const int* find_ptr( const std::vector<int>& vec, int elem )
{
    for ( size_t i = 0; i < vec.size(); i++ )
        if ( vec[ i ] == elem )
            return &vec[ i ];

    return nullptr;
}

// Generic find function returning an iterator
template <class T>
typename std::vector<T>::const_iterator
find( const std::vector<T>& vec, const T& elem )
{
    typename std::vector<T>::const_iterator   it = vec.begin();

    for ( ; it != vec.end(); it++ )
        if ( *it == elem )
            break;

    return it;
}

int main()
{
    // Finding with pointers
    std::vector<int>    vec     = { 5, 10, 12, 43, -123, -4, 3, 1 };
    const int*          pFour   = find_ptr( vec, -4 );

    if ( pFour )
    {
        std::cout << "Found -4 with index: " << pFour - &vec[ 0 ] << "\n";
    }
    else
    {
        std::cout << "-4 not found\n";
    }

    // Finding with iterators
    std::vector<int>::const_iterator    it  = find( vec, -4 );

    if ( it != vec.end() )
    {
        std::cout << "Found -4 with index: " << it - vec.begin() << "\n";
    }
    else
    {
        std::cout << "-4 not found\n";
    }

    return 0;
}
