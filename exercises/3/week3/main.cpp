#include <iostream>
#include <string>
#include "stack/lstack.hpp"

bool isOpeningSmallParenthesis(char c)
{
    return '(' == c;
}

bool isOpeningMediumParenthesis(char c)
{
    return '[' == c;
}

bool isOpeningLargeParenthesis(char c)
{
    return '{' == c;
}

bool isClosingSmallParenthesis(char c)
{
    return ')' == c;
}

bool isClosingMediumParenthesis(char c)
{
    return ']' == c;
}

bool isClosingLargeParenthesis(char c)
{
    return '}' == c;
}

bool hasValidSmallParenthesis(const std::string &expr)
{
    int notClosedOpenParenthesis = 0;
    for (char c : expr)
    {
        if (isOpeningSmallParenthesis(c))
        {
            notClosedOpenParenthesis++;
        }
        else if (isClosingSmallParenthesis(c))
        {
            notClosedOpenParenthesis--;
            if (notClosedOpenParenthesis < 0)
            {
                return false;
            }
        }
    }
    return 0 == notClosedOpenParenthesis;
}

bool hasValidParenthesisWithCounters(const std::string &expr)
{
    int notClosedOpenSmallParenthesis = 0;  // count for (
    int notClosedOpenMediumParenthesis = 0; // count for [
    int notClosedOpenLargeParenthesis = 0;  // count for {
    for (char c : expr)
    {
        if (isOpeningSmallParenthesis(c))
        {
            notClosedOpenSmallParenthesis++;
        }
        else if (isOpeningMediumParenthesis(c))
        {
            notClosedOpenMediumParenthesis++;
        }
        else if (isOpeningLargeParenthesis(c))
        {
            notClosedOpenLargeParenthesis++;
        }
        else if (isClosingSmallParenthesis(c))
        {
            notClosedOpenSmallParenthesis--;
            if (notClosedOpenSmallParenthesis < 0)
            {
                return false;
            }
        }
        else if (isClosingMediumParenthesis(c))
        {
            notClosedOpenMediumParenthesis--;
            if (notClosedOpenMediumParenthesis < 0 || notClosedOpenSmallParenthesis > 0)
            {
                return false;
            }
        }
        else if (isClosingLargeParenthesis(c))
        {
            notClosedOpenLargeParenthesis--;
            if (notClosedOpenLargeParenthesis < 0 || notClosedOpenMediumParenthesis > 0 || notClosedOpenSmallParenthesis > 0)
            {
                return false;
            }
        }
    }
    return 0 == notClosedOpenSmallParenthesis && 0 == notClosedOpenMediumParenthesis && 0 == notClosedOpenLargeParenthesis;
}

bool isOpeningParenthesis(char c)
{
    return isOpeningSmallParenthesis(c) || isOpeningMediumParenthesis(c) || isOpeningLargeParenthesis(c);
}

bool isClosingParenthesis(char c)
{
    return isClosingSmallParenthesis(c) || isClosingMediumParenthesis(c) || isClosingLargeParenthesis(c);
}

bool isMatchingParenthesis(char opening, char closing)
{
    if (isOpeningSmallParenthesis(opening))
    {
        return isClosingSmallParenthesis(closing);
    }
    if (isOpeningMediumParenthesis(opening))
    {
        return isClosingMediumParenthesis(closing);
    }
    if (isOpeningLargeParenthesis(opening))
    {
        return isClosingLargeParenthesis(closing);
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
    std::cout << "hasValidSmallParenthesis('(())'): \t" << hasValidSmallParenthesis("(())") << std::endl;
    std::cout << "hasValidSmallParenthesis('()()()((())) '): \t" << hasValidSmallParenthesis("()()()((())) ") << std::endl;
    std::cout << "hasValidSmallParenthesis(')('): \t" << hasValidSmallParenthesis(")(") << std::endl;
    std::cout << "hasValidSmallParenthesis('(()))'): \t" << hasValidSmallParenthesis("(()))") << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "hasValidParenthesisWithCounters('{[()]}'): \t" << hasValidParenthesisWithCounters("{[()]}") << std::endl;
    std::cout << "hasValidParenthesisWithCounters('{[][]()()()[()]}'): \t" << hasValidParenthesisWithCounters("{[][]()()()[()]}") << std::endl;
    std::cout << "hasValidParenthesisWithCounters('{}[]()'): \t" << hasValidParenthesisWithCounters("{}[]()") << std::endl;
    std::cout << "hasValidParenthesisWithCounters('{([])}'): \t" << hasValidParenthesisWithCounters("{([])}") << std::endl;
    std::cout << "hasValidParenthesisWithCounters('[{()}]'): \t" << hasValidParenthesisWithCounters("[{()}]") << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "hasValidParenthesis('{[()]}'): \t" << hasValidParenthesis("{[()]}") << std::endl;
    std::cout << "hasValidParenthesis('{[][]()()()[()]}'): \t" << hasValidParenthesis("{[][]()()()[()]}") << std::endl;
    std::cout << "hasValidParenthesis('{}[]()'): \t" << hasValidParenthesis("{}[]()") << std::endl;
    std::cout << "hasValidParenthesis('{([])}'): \t" << hasValidParenthesis("{([])}") << std::endl;
    std::cout << "hasValidParenthesis('[{()}]'): \t" << hasValidParenthesis("[{()}]") << std::endl;

    return 0;
}