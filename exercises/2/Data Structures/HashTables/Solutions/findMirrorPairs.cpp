// Solution: https://www.techiedelight.com/find-symmetric-pairs-array-pairs/

#include <iostream>
#include <unordered_set>
#include <string> // std::to_string
using namespace std;

// data structure to store a pair (or use std::pair)
struct Pair {
    int x, y;
};

string constructStringPair( int x, int y )
{
    return "{" + to_string( x ) + ", " + to_string( y ) + "}";
}
//"{x, y}"

// Function to find all pairs that are mirror of each other
// Time complexity: O(n)
// Space complexity: O(n)
void findPairs( const std::vector<Pair>& pairs )
{
    // create an empty set of strings
    unordered_set<string> set;

    // do for each pair
    for ( const Pair& p_iter : pairs )
    {
        // construct a pair (x, y) from pairs[i]
        string p = constructStringPair( p_iter.x, p_iter.y ); //"{x, y}"

        // insert current pair into the set
        set.insert( p );

        // construct mirror pair (y, x) of pairs[i]
        string reverse_pair = constructStringPair( p_iter.y, p_iter.x );

        // if mirror pair if seen before, print the pairs
        if ( set.find( reverse_pair ) != set.end() )
            cout << p << " | " << reverse_pair << '\n';
    }
}

int main()
{
    std::vector<Pair> pairs = { {3, 4}, {1, 2}, {5, 2}, {7, 10}, {4, 3}, {2, 5} };
    findPairs(pairs);

    return 0;
}