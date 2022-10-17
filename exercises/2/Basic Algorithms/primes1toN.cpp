#include <iostream>

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
        while ( i <= sq )
        {
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

void primes1toN( const uint32_t& N ) // the slow way to approach this problem
{
    for ( uint32_t i = 2; i <= N; ++i )
    {
        if ( isPrime2( i ) )
        {
            printf( "%5u", i );
        }
    }
}

// Търсене на прости числа в интервал
// Сито на Ератостен
// Sieve of Eratosthenes
// Първо идея, после реализация

#define MAXN 30000
bool sieve[MAXN]; // допълнителна памет! не е много добре това :/
void eratosten( unsigned n )
{
    unsigned j, i = 2;
    while ( i <= n )
    {
        if ( !sieve[ i ] )
        {
            printf( "%5u", i );
            j = i * i;
            while ( j <= n )
            {
                sieve[ j ] = true;
                j += i;
            }
        }
        i++;
    }
}
// използваме сито на Ератостен, ако имаме нужда от това да пазим простите числа в интервал [ k , n ]
// например, ако постоянно "питаме" дали число в този интервал е просто, операцията за проверка ще е O(1)


int main()
{
    const unsigned n = 1200;
    primes1toN( n );
    std::cout << "\n\n";
    for ( unsigned i = 0; i < n; i++ ) sieve[i] = false;

    eratosten( n );
    return 0;
}