#ifndef __RPN_CALCULATOR_HPP
#define __RPN_CALCULATOR_HPP
#include <string>
#include "lstack.hpp"

class RPNCalculator {
private:
    LinkedStack<double> resultStack;

    static bool isdigit(char c);
    static bool isop(char c);
    static double digitToValue(char c);
    static double calculate(double left, char op, double right);

public:
    double calculateFromRPN(std::string const& s);
};

#endif