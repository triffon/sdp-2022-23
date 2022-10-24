#include <iostream>
#include <vector>

template <class T>
typename std::vector<T> reversed( const std::vector<T>& vec )
{
    std::vector<T>  res;
    res.reserve( vec.size() );

    using criterator_t  = typename std::vector<T>::const_reverse_iterator;
    criterator_t it     = vec.crbegin();

    for ( ; it != vec.crend(); it++ )
        res.push_back( *it );

    return res;
}

int main()
{
    std::vector<int>    vec     = { 5, 10, 12, 43, -123, -4, 3, 1 };
    std::vector<int>    revVec  = reversed( vec );

    for ( int elem : revVec )
    {
        std::cout << elem << " ";
    }

    return 0;
}
