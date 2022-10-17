#include <iostream>
#include <cmath>    // sqrt(...)

bool isPrimeOptimized( size_t num );

// Generic way in O(n*sqrt(n)) time
void allPrimesUpToLazy( size_t num )
{
    for ( size_t i = 2; i <= num; i++ )
        if ( isPrimeOptimized( i ) )
            std::cout << i << ' ';
}

// Eratosthenes sieve in O(n*log(log(n))) time and O(n) space
// Note: The sieve can be implemented in O(n) time
void allPrimesUpToSieve( size_t num )
{
    constexpr size_t    MAX     = 4096;

    if ( num >= MAX )
    {
        std::cout << "Too much to handle...";
        return;
    }

    bool    arrIsComposite[ MAX ]   = { false, };

    for ( size_t i = 2; i <= num; i++ )
    {
        if ( ! arrIsComposite[ i ] )
        {
            std::cout << i << ' ';

            for ( size_t j = 2 * i; j <= num; j += i )
                arrIsComposite[ j ] = true;
        }
    }
}

int main()
{
    allPrimesUpToLazy( 512 );
    std::cout << '\n';
    allPrimesUpToSieve( 512 );
    std::cout << '\n';

    return 0;
}



bool isPrimeOptimized( size_t num )
{
    if ( num < 2 )
        return false;

    if ( num == 2 )
        return true;

    if ( num % 2 == 0 )
        return false;

    size_t  root    = sqrt( num );
    for ( size_t i = 3; i <= root; i += 2 )
        if ( num % i == 0 )
            return false;

    return true;
}
