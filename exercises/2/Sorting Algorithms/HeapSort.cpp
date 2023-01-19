#include <iostream>
#include <vector>

void heapify( std::vector<int>& arr, int n, int i )
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if ( l < n && arr[ l ] > arr[ largest ] )
        largest = l;

    // If right child is larger than largest so far
    if ( r < n && arr[ r ] > arr[ largest ] )
        largest = r;

    // If largest is not root
    if ( largest != i )
    {
        std::swap( arr[ i ], arr[ largest ] );

        // Recursively heapify the affected sub-tree
        heapify( arr, n, largest );
    }
}

// main function to do heap sort
void heapSort( std::vector<int>& arr )
{
    size_t n = arr.size();
    // Build heap (rearrange array)
    for ( int i = n / 2 - 1; i >= 0; i-- )
        heapify( arr, n, i );

    // One by one extract an element from heap
    for ( int i = n - 1; i > 0; i-- )
    {
        // Move current root to end
        std::swap( arr[ 0 ], arr[ i ] );

        // call max heapify on the reduced heap
        heapify( arr, i, 0 );
    }
}


/* A utility function to print array of size n */
void printArray( std::vector<int>& arr )
{
    for ( int el : arr )
        std::cout << el << " ";

    std::cout << std::endl;
}

int main()
{
    std::vector<int> arr = { 1, 12, 9, 5, 6, 10 };

    heapSort( arr );

    std::cout << "Sorted array is \n";
    printArray( arr );
}