#include <iostream>
#include <algorithm>
#include <vector>

template <class T>
typename std::vector<T>::const_iterator
    kthElement( const std::vector<T>& vec, size_t kth )
{
    using iter  = typename std::vector<T>::iterator;

    if ( kth > vec.size() || kth == 0 )
    {
        throw std::logic_error( "Invalid kth element range!" );
    }

    // Space complexity: O(n)
    std::vector<T>  helper  = vec;      // Copies the vector in O(n) time
    for ( size_t i = 0; i < kth; i++ )  // Runs k times
    {
        iter    curr    = helper.begin() + i;
        iter    minIt   = std::min_element( curr, helper.end() );   // Finds min in O(n) time
        std::iter_swap( curr, minIt );
    }

    return std::find( vec.begin(), vec.end(), helper[ kth - 1 ] );  // Find it in the original vector in O(n) time

    // Overall time complexity:  O(n*k)
    // Overall space complexity: O(n)
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
    std::cout << "2-nd smallest element:\t" << *kthElement( vec, 2 ) << "\n";
    std::cout << "4-th smallest element:\t" << *kthElement( vec, 4 ) << "\n";

    return 0;
}
