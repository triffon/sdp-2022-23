#include <iostream>
#include <string>
#include <vector>
#include "stack/lstack.hpp"

const std::vector<std::pair<char, char>> parenthesis = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

bool isOpeningParenthesis(char c)
{
    for (std::pair<char, char> p : parenthesis)
    {
        if (p.first == c)
        {
            return true;
        }
    }
    return false;
}

bool isClosingParenthesis(char c)
{
    for (std::pair<char, char> p : parenthesis)
    {
        if (p.second == c)
        {
            return true;
        }
    }
    return false;
}

bool isMatchingParenthesis(char opening, char closing)
{
    for (std::pair<char, char> p : parenthesis)
    {
        if (p.first == opening)
        {
            return p.second == closing;
        }
    }
    return false;
}

bool hasValidParenthesis(const std::string &expr)
{
    LinkedStack<char> notClosedOpenParenthesis;
    for (char c : expr)
    {
        if (isOpeningParenthesis(c))
        {
            notClosedOpenParenthesis.push(c);
        }
        else if (isClosingParenthesis(c))
        {
            if (!isMatchingParenthesis(notClosedOpenParenthesis.pop(), c))
            {
                return false;
            }
        }
    }
    return notClosedOpenParenthesis.empty();
}

int main()
{
    std::cout << "hasValidParenthesis('{[()]}'): \t" << hasValidParenthesis("{[()]}") << std::endl;
    std::cout << "hasValidParenthesis('{[][]()()()[()]}'): \t" << hasValidParenthesis("{[][]()()()[()]}") << std::endl;
    std::cout << "hasValidParenthesis('{}[]()'): \t" << hasValidParenthesis("{}[]()") << std::endl;
    std::cout << "hasValidParenthesis('{([])}'): \t" << hasValidParenthesis("{([])}") << std::endl;
    std::cout << "hasValidParenthesis('[{()}]'): \t" << hasValidParenthesis("[{()}]") << std::endl;

    return 0;
}