#include <iostream>

// Проверка дали дадено число е просто
bool isPrime0( unsigned n ) /* връща true, ако е просто, и false – при съставно */
{
    bool result = true;
    if ( n == 1 )
    {
        result = false;
    }
    else if ( n >= 2 )
    {
        unsigned i = 2;
        std::cout << "N = " << n << " is checked with ";
        while ( i < n )
        {
            std::cout << i << " ";
            if ( n % i == 0 )
            {
                result = false;
                break;
            }
            i++;
        }
    }

    return result;
}

// Проверка дали дадено число е просто
bool isPrime1( unsigned n ) /* връща true, ако е просто, и false – при съставно */
{
    bool result = true;
    if ( n == 1 )
    {
        result = false;
    }
    else if ( n >= 2 )
    {
        unsigned i = 2;
        std::cout << "N = " << n << " is checked with ";
        while ( i <= ( n / 2 - 1 ) )
        {
            std::cout << i << " ";
            if ( n % i == 0 )
            {
                result = false;
                break;
            }
            i++;
        }
    }
    
    return result;
}

// Да сравним колко стъпки се правят в isPrime1 и isPrime2
bool isPrime2( unsigned n ) /* връща true, ако е просто, и false – при съставно */
{
    bool result = true;
    if ( n == 1 )
    {
        result = false;
    }
    else if ( n >= 2 )
    {
        unsigned i = 2;
        double sq = sqrt( n );
        std::cout << "N = " << n << " is checked with ";
        while ( i <= sq )
        {
            std::cout << i << " ";
            if ( n % i == 0 )
            {
                result = false;
                break;
            }
            i++;
        }
    }
    return result;
}


int main()
{
    uint32_t n;
    std::cin >> n;
    std::cout << ( isPrime0( n ) ? "; N is prime" : "; N is not prime" ) << std::endl;
    std::cout << ( isPrime1( n ) ? "; N is prime" : "; N is not prime" ) << std::endl;
    std::cout << ( isPrime2( n ) ? "; N is prime" : "; N is not prime" ) << std::endl;

    return 0;
}