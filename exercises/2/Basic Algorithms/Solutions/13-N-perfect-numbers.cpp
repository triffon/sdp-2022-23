#include <iostream>

bool isPerfectNumber(const unsigned int number)
{
    int sumOfDevisors = 1; // 1 divide every number
    for (int i = 2; i < number / 2 + 1; i++)
    {
        if (number % i == 0)
            sumOfDevisors += i;
    }
    return sumOfDevisors == number;
}
void nPerfectNumbers( size_t n )
{
    uint64_t tryWithThisNumber = 0;
    for ( size_t tries = 0; tries < n; ++tryWithThisNumber )
    {
        if ( isPerfectNumber( tryWithThisNumber ) )
        {
            ++tries;
            std::cout << tryWithThisNumber << std::endl;
        }
    }
}

int main()
{
    uint32_t n;
    std::cin >> n;
    nPerfectNumbers( n );
    return 0;
}