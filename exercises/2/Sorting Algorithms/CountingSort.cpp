#include <iostream>
#include <vector>
#include <algorithm>

void countingSort( std::vector<int>& vec )
{
    // Counting sort has a time complexity of:
    //   O( n + diff ), where diff = maxElem - minElem + 1, and n = number of elements in the array
    //   Note: if ( diff < n*log(n) ) => { Counting Sort - ОК } else { Dont't use Counting Sort! }
    //
    // Counting sort also has an aditional space complexity of: O( diff )

    // In this case we have [ 50, 2, 3, 6, 1, 0, 4 ]:
    //   n = 7,  n^2 = 49 |
    //   diff = 51 > n^2  | => Counting sort O( n + diff ) == O( n + n^2 ) == O( n^2 )
    //   Warning: Counting sort will be as slow as or slower than a normal comparison sort in this case!

    int diff = *std::max_element( vec.begin(), vec.end() ) - *std::min_element( vec.begin(), vec.end() ) + 1;
    std::vector<int> countArr( diff, 0 );

    for ( size_t i = 0; i < vec.size(); i++ )   // O( n )
        ++countArr[ vec[ i ] ];

    int resIndex = 0;
    for ( size_t i = 0; i < countArr.size(); i++ )  // O( diff )
    {
        while ( countArr[ i ] > 0 )
        {
            vec[ resIndex ] = i;    // The total of these operations is O( n )
            --countArr[ i ];        // therefore the whole `for` cycle will have
            ++resIndex;             // a time complexity of O( max( diff, n ) )
        }
    }
}


int main()
{
    std::vector<int> arr = { 50, 2, 3, 6, 1, 0, 4 };

    countingSort( arr );

    std::cout << "Counting sorted: ";
    for ( int elem : arr )
        std::cout << elem << " ";

    std::cout << "\n";

    return 0;
}
