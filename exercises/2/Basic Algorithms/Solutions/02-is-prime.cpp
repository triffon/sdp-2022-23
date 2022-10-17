#include <iostream>
#include <cmath>    // sqrt(...)

// Generic way in O(n) time, where n is the number itself
bool isPrimeGeneric( size_t num )
{
    if ( num < 2 )
        return false;   // 0 and 1 aren't primes

    if ( num == 2 )
        return true;    // 2 is a prime

    if ( num % 2 == 0 )
        return false;   // no even number is a prime (except 2)

    // Check all odd numbers from 3 to num
    for ( size_t i = 3; i < num; i += 2 )
        if ( num % i == 0 )
            return false;

    return true;
}

// Sqrt optimization in O(sqrt(n)) time
bool isPrimeOptimized( size_t num )
{
    if ( num < 2 )
        return false;

    if ( num == 2 )
        return true;

    if ( num % 2 == 0 )
        return false;

    // Check all odd numbers from 3 to sqrt( num )
    size_t  root    = sqrt( num );
    for ( size_t i = 3; i <= root; i += 2 )
        if ( num % i == 0 )
            return false;

    return true;
}

int main()
{
    std::cout << std::boolalpha;
    std::cout << isPrimeOptimized( 2147483647 ) << '\n';
    std::cout << isPrimeGeneric( 2147483647 ) << '\n';

    // Run to clearly see how much faster the optimized version is (1st in the output)

    return 0;
}
