#include <iostream>
#include <vector>

template <class T>
typename std::vector<T>::const_iterator find( const std::vector<T>& vec, const T& elem )
{
    typename std::vector<T>::const_iterator   it = vec.begin();

    for ( ; it != vec.end(); it++ )
        if ( *it == elem )
            break;

    return it;
}

int main()
{
    std::vector<int>                    vec = { 5, 10, 12, 43, -123, -4, 3, 1 };
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
