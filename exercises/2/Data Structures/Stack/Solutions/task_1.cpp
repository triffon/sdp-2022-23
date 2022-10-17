#include <iostream>
#include <string>
#include <stack>

char openingBracket(char bracket)
{
	switch (bracket)
	{
	case ')':
		return '(';
	case ']':
		return '[';
	case '}':
		return '{';
	}

	return bracket;
}

bool isCorrectExpression(const std::string& expr)
{
	std::stack<char> stack;

	for (const char& ch : expr)
	{
		switch (ch)
		{
		case '(':
		case '[':
		case '{':
			stack.push(ch);
			break;

		case ')':
		case ']':
		case '}':
			if (!stack.empty() && stack.top() == openingBracket(ch))
				stack.pop();
			else
				return false;
		}
	}

	return stack.empty();
}

int main()
{

	std::string str;
	std::getline(std::cin, str);

	std::cout << isCorrectExpression(str);

	return 0;
}