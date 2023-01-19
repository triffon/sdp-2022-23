#include <iostream>
#include <vector>
#include <cassert>

const int MAX = 50;

void merge( int arr[], int left, int mid, int right )
{
    int leftArrSize     = mid - left + 1;
    int rightArrSize    = right - mid;

    int leftArr[ MAX ];
    int rightArr[ MAX ];

    for ( int i = 0; i < leftArrSize; i++ )
        leftArr[ i ] = arr[ left + i ];

    for ( int j = 0; j < rightArrSize; j++ )
        rightArr[ j ] = arr[ mid + 1 + j ];

    int leftArrIndex = 0;
    int rightArrIndex = 0;
    int mergedArrIndex = left;

    while ( leftArrIndex < leftArrSize && rightArrIndex < rightArrSize )
    {
        if ( leftArr[ leftArrIndex ] < rightArr[ rightArrIndex ] )
        {
            arr[ mergedArrIndex ] = leftArr[ leftArrIndex ];
            leftArrIndex++;
        }
        else
        {
            arr[ mergedArrIndex ] = rightArr[ rightArrIndex ];
            rightArrIndex++;
        }
        mergedArrIndex++;
    }

    while ( leftArrIndex < leftArrSize )
    {
        arr[ mergedArrIndex ] = leftArr[ leftArrIndex ];
        leftArrIndex++;
        mergedArrIndex++;
    }

    while ( rightArrIndex < rightArrSize )
    {
        arr[ mergedArrIndex ] = rightArr[ rightArrIndex ];
        rightArrIndex++;
        mergedArrIndex++;
    }
}


void mergeSortRec( int arr[], int left, int right )
{
    // Merge sort has a time complexity of O( n*log(n) )
    // and typically an aditional space complexity of O( n )

    if ( left >= right )
        return;

    int mid = ( left + right - 1 ) / 2;
    mergeSortRec( arr, left, mid );
    mergeSortRec( arr, mid + 1, right );
    merge( arr, left, mid, right );
}

// Merge sort steps:
// [ 50, 2, 3, 6, 1, 0, 4 ] left = 0, mid = 2, right = 6
// [ 50, 2, 3 ] [ 6, 1, 0, 4 ] left = 0, mid = 0, right = 2
// [ 50 ] [ 2, 3 ] [ 6, 1, 0, 4 ]
// [ 50 ] [ 2, 3 ] [ 6, 1, 0, 4 ]
// [ 50 ] [ 2 ] [ 3 ] [ 6, 1, 0, 4 ]
// [ 50 ] [ 2 ] [ 3 ] [ 6, 1, 0, 4 ]
// [ 50 ] [ 2 ] [ 3 ] [ 6, 1, 0, 4 ]
// [ 50 ] [ 2, 3 ] [ 6, 1, 0, 4 ]
// [ 2, 3, 50 ] [ 6, 1, 0, 4 ]
// [ 2, 3, 50 ] [ 6, 1 ] [ 0, 4 ]
// [ 2, 3, 50 ] [ 6 ] [ 1 ] [ 0, 4 ]
// [ 2, 3, 50 ] [ 6 ] [ 1 ] [ 0, 4 ]
// [ 2, 3, 50 ] [ 6 ] [ 1 ] [ 0, 4 ]
// [ 2, 3, 50 ] [ 1, 6 ] [ 0, 4 ]
// [ 2, 3, 50 ] [ 1, 6 ] [ 0 ] [ 4 ]
// [ 2, 3, 50 ] [ 1, 6 ] [ 0 ] [ 4 ]
// [ 2, 3, 50 ] [ 1, 6 ] [ 0 ] [ 4 ]
// [ 2, 3, 50 ] [ 1, 6 ] [ 0, 4 ]
// [ 2, 3, 50 ] [ 0, 1, 4, 6 ]
// [ 0, 1, 2, 3, 4, 6, 50 ]


void mergeSort( int arr[], int size )
{
    mergeSortRec( arr, 0, size - 1 );
}


void mergeSort( std::vector<int>& vec )
{
    assert( ( "Merge Sort works only with arrays with max size of MAX", vec.size() <= MAX ) );
    mergeSort( vec.data(), vec.size() );
}


int main()
{
    std::vector<int> arr = { 50, 2, 3, 6, 1, 0, 4 };

    mergeSort( arr );

    std::cout << "Merge sorted: ";
    for ( int elem : arr )
        std::cout << elem << " ";

    std::cout << "\n";

    return 0;
}
