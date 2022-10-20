#ifndef __RPN_CALCULATOR_HPP
#define __RPN_CALCULATOR_HPP
#include <string>
#include "lstack.hpp"
#include "calculator.hpp"

class RPNCalculator : public Calculator {
private:
    LinkedStack<double> resultStack;
    LinkedStack<char> operationStack;

    static bool isdigit(char c);
    static bool isop(char c);
    static double digitToValue(char c);
    static double applyOperation(double left, char op, double right);
    static unsigned priority(char op);

public:
    double calculateFromRPN(std::string const& s);
    std::string toRPN(std::string const& s);
    double calculate(std::string const& s);
};

#endif