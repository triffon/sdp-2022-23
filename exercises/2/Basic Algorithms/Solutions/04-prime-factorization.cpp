#include <iostream>
#include <cmath>    // sqrt(...)

// Prime factorization in O(sqrt(n)) time
void printPrimeFactors( size_t num )
{
    // This while loop runs in O(log(n)) time
    while ( num % 2 == 0 )
    {
        std::cout << 2 << ' ';
        num /= 2;
    }

    // This for loop runs in O(sqrt(n)) time
    size_t  root    = sqrt( num );
    for ( size_t i = 3; i <= root; i += 2 )
    {
        while ( num % i == 0 )
        {
            std::cout << i << ' ';
            num /= i;
        }
    }

    // Simple check - O(1) time
    if ( num > 2 )
        std::cout << num << ' ';

    // As a total result: O(log(n)) + O(sqrt(n)) + O(1)
    // Taking the fastest growing function yields O(sqrt(n)) time
    //
    // Compared to the generic method of iterating over all numbers
    // from 2 to num, checking whether it's divisible by the number
    // and then checking if that number is prime.
    // Which will run in O(n*sqrt(n)) time
}

int main()
{
    printPrimeFactors( 24708 );
    std::cout << '\n';

    return 0;
}
