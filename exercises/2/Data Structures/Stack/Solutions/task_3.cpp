#include "TemplateStack.hpp"

const size_t MAX_SIZE_BUFFER = 1024;

int main()
{
	dsa::TemplateStack<char> sentence;

	char buffer[ MAX_SIZE_BUFFER ];

	std::cin.getline( buffer, MAX_SIZE_BUFFER );

	size_t i = 0;
	while ( buffer[ i ] )
	{
		sentence.push( buffer[ i++ ] );
	}

	while ( !sentence.empty() )
	{
		std::cout << sentence.top();
		sentence.pop();
	}

	return 0;
}