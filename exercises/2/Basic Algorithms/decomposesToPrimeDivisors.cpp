#include <iostream>

void decomposesToPrimeDivisors( uint32_t k )
{
    for ( int i = 2; i <= k; ++i )
    {
        while ( k % i == 0 )
        {
            std::cout << i << " ";
            k /= i;
        }
    }
}

int main()
{
    uint32_t k;
    std::cout << "Enter positive number: ";
    std::cin >> k;

    decomposesToPrimeDivisors( k );
    
    return 0;
}