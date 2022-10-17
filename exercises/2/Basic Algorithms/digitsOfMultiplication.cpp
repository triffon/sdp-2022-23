#include <iostream>


int main()
{
	uint32_t k, n;
	std::cout << "Enter two positive numbers: ";
	std::cin >> k >> n;

	uint64_t result = k * n;
		std::cout << "1. Count of digits is: " << int(log10( result )) + 1 << std::endl;
	// or
	size_t digits;
	for (digits = 0; result > 0; result /= 10, digits++);
	std::cout << "2. Count of digits is: " << digits << std::endl;


	// but the result may quickly be overflow :/
	// try with k = 4 000 000 000 and n = 4 000 000 000 :)
	// we can use dark magic( math ) to resolve this problem

	std::cout << "3. Count of digits is: " << int(log10( k ) + log10( n )) + 1 << std::endl;

	return 0;
}