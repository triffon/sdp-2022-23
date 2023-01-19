// Solution: https://www.techiedelight.com/probability-alive-after-taking-n-steps-island/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
//#include <boost/functional/hash.hpp>

using namespace std;

#define N 3

// Find the probability that person is alive after he walks n steps
// from location (x, y) on the island
double aliveProbability( int x, int y, int steps_left, unordered_map<string, double>& dp )
{
    // base case
    if ( steps_left == 0 )
        return 1.0;
  
    // calculate unique map key from current coordinates(x, y) of person
    // and number of steps(n) left
    string key = to_string( x ) + "|" + to_string( y ) + "|" + to_string( steps_left );
    //"0|0|4" -> [0;1]

    // if sub-problem is seen for the first time
    if ( dp.find( key ) == dp.end() )
    {
        double p = 0.0;

        // move one step up
        if ( y > 0 )
            p += 0.25 * aliveProbability( x, y - 1, steps_left - 1, dp );

        // move one step down
        if ( y < N - 1 )
            p += 0.25 * aliveProbability( x, y + 1, steps_left - 1, dp );

        // move one step left
        if ( x > 0 )
            p += 0.25 * aliveProbability( x - 1, y, steps_left - 1, dp );

        // move one step right
        if ( x < N - 1 )
            p += 0.25 * aliveProbability( x + 1, y, steps_left - 1, dp );

        dp[ key ] = p;
    }

    return dp[ key ];
}

struct Cell
{
    int x, y, n;
};

bool operator==( const Cell& lhs, const Cell& rhs )
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.n == rhs.n;
}

struct MyHash
{
    std::size_t operator()( const Cell& cell ) const noexcept
    {
        std::cout << "Using MyHash" << std::endl;
        std::hash<int> XHash;
        std::size_t h1 = XHash(cell.x);
        std::size_t h2 = std::hash<int>{}(cell.y);
        std::size_t h3 = std::hash<int>{}(cell.n);
        return h1 ^ (h2 << 1) ^ (h3 << 2); // or use boost::hash_combine
    }
};

// custom specialization of std::hash can be injected in namespace std
namespace std
{
    template<> 
    struct hash<Cell>
    {
        std::size_t operator()( const Cell& cell) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(cell.x);
            std::size_t h2 = std::hash<int>{}(cell.y);
            std::size_t h3 = std::hash<int>{}(cell.n);
            return h1 ^ (h2 << 1) ^ (h3 << 2); // or use boost::hash_combine

            //size_t seed = 0;
            //hash_combine( seed, cell.x );
            //hash_combine( seed, cell.y );
            //hash_combine( seed, cell.steps_left );
            //return seed;
        }
    };
}

struct Cell1
{
    int x, y, n;

    bool operator==( const Cell& rhs )
    {
        return x == rhs.x && y == rhs.y && n == rhs.n;
    }

    struct Hash
    {
        size_t operator()( const Cell& cell ) const noexcept
        {
            std::hash<int> XHash;
            std::size_t h1 = XHash( cell.x );
            std::size_t h2 = std::hash<int> {}( cell.y );
            std::size_t h3 = std::hash<int> {}( cell.n );
            return h1 ^ ( h2 << 1 ) ^ ( h3 << 2 ); // or use boost::hash_combine
        }
    };
};

double aliveProbability( int x, int y, int n, unordered_map<Cell1, double, Cell1::Hash>& dp )
{
    // base case
    if ( n == 0 )
        return 1.0;

    // calculate unique map key from current coordinates(x, y) of person
    // and number of steps(n) left
    Cell1 key = { x, y, n };

    // if sub-problem is seen for the first time
    if ( dp.find( key ) == dp.end() )
    {
        double p = 0.0;

        // move one step up
        if ( y > 0 )
            p += 0.25 * aliveProbability( x, y - 1, n - 1, dp );

        // move one step down
        if ( y < N - 1 )
            p += 0.25 * aliveProbability( x, y + 1, n - 1, dp );

        // move one step left
        if ( x > 0 )
            p += 0.25 * aliveProbability( x - 1, y, n - 1, dp );

        // move one step right
        if ( x < N - 1 )
            p += 0.25 * aliveProbability( x + 1, y, n - 1, dp );

        dp[ key ] = p;
    }

    return dp[ key ];
}

int main()
{
    int n = 4;        // number of steps to be taken
    int x = 0, y = 0; // starting coordinates

    // map to store solution to already computed sub-problems
    //unordered_map<string, double> dp; // with key 'string'
    unordered_map<Cell1, double, Cell1::Hash> dp; // with key 'Cell1' and hash function Cell1::Hash
    //unordered_map<Cell, double> dp; // with key 'Cell' and hash function that is injected in namespace std 

    // calculate alive Probability
    cout << "Alive probability is " << aliveProbability(x, y, n, dp);

    return 0;
}