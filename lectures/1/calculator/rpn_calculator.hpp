#ifndef __RPN_CALCULATOR_HPP
#define __RPN_CALCULATOR_HPP
#include <string>
#include "lstack.hpp"
#include "calculator.hpp"

class RPNCalculator : public Calculator {
private:
    LinkedStack<double> resultStack;
    LinkedStack<char> operationStack;

public:
    double calculateFromRPN(std::string const& s);
    std::string toRPN(std::string const& s);
    double calculate(std::string const& s);
};

#endif