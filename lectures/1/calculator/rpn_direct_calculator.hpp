#ifndef __RPN_DIRECT_CALCULATOR_HPP
#define __RPN_DIRECT_CALCULATOR_HPP

#include "lstack.hpp"
#include "calculator.hpp"

class RPNDirectCalculator : public Calculator {
private:
    LinkedStack<double> resultStack;
    LinkedStack<char> operationStack;

    void processOperation(char op);

public:
    double calculate(std::string const& s);
};

#endif