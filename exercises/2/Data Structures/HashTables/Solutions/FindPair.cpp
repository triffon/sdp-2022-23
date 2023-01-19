// Solution from https://www.techiedelight.com/find-pair-with-given-sum-array/

#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <unordered_set>

// Naive method to find a pair in an array with a given sum
// Time complexity: O(n^2)
// Space complexity: O(1)
void findPair1( const std::vector<int>& arr, size_t n, int sum )
{
    // consider each element except the last
    for ( size_t i = 0; i < n - 1; i++ )
    {
        // start from the i'th element till the last element
        for ( size_t j = i + 1; j < n; j++ )
        {
            // if the desired sum is found, print it and return
            if ( arr[ i ] + arr[ j ] == sum )
            {
                std::cout << "Pair found at index " << i << " and " << j << std::endl;
                return;
            }
        }
    }

    // No pair with the given sum exists in the array
    std::cout << "Pair not found" << std::endl;
}

// Function to find a pair in an array with a given sum using sorting
// Time complexity: O(n*log(n))
// Space complexity: O(1)
void findPair2( std::vector<int> arr, size_t n, int sum )
{
    // sort the array in ascending order
    std::sort( arr.begin(), arr.end() );

    // maintain two indices pointing to end-points of the array
    int low = 0;
    int high = n - 1;

    // reduce the search space `arr[low…high]` at each iteration of the loop

    // loop till search space is exhausted
    while ( low < high )
    {
        // sum found
        if ( arr[ low ] + arr[ high ] == sum )
        {
            std::cout << "Pair found: (" << arr[ low ] << " + " << arr[ high ] << " ) " << std::endl;
            return;
        }

        // increment `low` index if the total is less than the desired sum;
        // decrement `high` index if the total is more than the desired sum
        ( arr[ low ] + arr[ high ] < sum ) ? low++: high--;
    }

    // No pair with the given sum exists in the array
    std::cout << "Pair not found";
}

// Function to find a pair in an array with a given sum using hashing
// Time complexity: O(n)
// Space complexity: O(n)
void findPair3( const std::vector<int>& arr, size_t n, int sum )
{
    // create an empty set
    // the key is actual value in array
    std::unordered_set<int> set;

    // do for each element
    for ( size_t i = 0; i < n; i++ )
    {
        std::unordered_set<int>::iterator it = set.find( sum - arr[ i ] );

        // check if sum-arr[i] exists
        if ( it != set.end() )
        {
            // if the difference is seen before, print the pair
            std::cout << "Pair found " << *it << " + " << arr[ i ];
            return;
        }

        // store actual value of the current element in the set
        set.insert( arr[ i ] );
    }

    // we reach here if pair is not found
    std::cout << "Pair not found";
}


int main()
{
    std::vector<int> arr = { 8, 7, 2, 5, 9, 3, 1 };
    int sum = 11;

    findPair1(arr, arr.size(), sum);
    findPair2(arr, arr.size(), sum);
    findPair3(arr, arr.size(), sum);

    return 0;
}