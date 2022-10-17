#include <iostream>
#include <cmath>    // log10(...)

using   ull_t   = unsigned long long;

// Generic way in O(n) time, where n is the number of digits of the product
size_t numOfDigitsInProductGeneric( size_t num1, size_t num2 )
{
    if ( num1 == 0 || num2 == 0 )
        return 0;

    size_t  digitsCnt   = 0;
    ull_t   product     = (ull_t) num1 * num2;
    while ( product > 0 )
    {
        product /= 10;
        digitsCnt++;
    }

    return digitsCnt;
}

// Maths trick in O(1) time
size_t numOfDigitsInProductMaths( size_t num1, size_t num2 )
{
    return (size_t)( log10( num1 ) + log10( num2 ) + 1 );
}

int main()
{
    std::cout << numOfDigitsInProductGeneric( 123, 452 ) << '\n';   // 123 * 452 = 55596    ; that's five digits
    std::cout << numOfDigitsInProductMaths( 123, 452 ) << '\n';     // 123 * 452 = 55596    ; that's five digits

    return 0;
}
