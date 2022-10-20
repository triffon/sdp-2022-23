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


int main()
{
    uint32_t n;
    std::cin >> n;
    std::cout << n << ( isPerfectNumber( n ) ? " is perfect number" : " is not perfect number" ) << std::endl;

    return 0;
}