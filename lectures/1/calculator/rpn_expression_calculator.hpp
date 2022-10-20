#ifndef __RPN_EXPRESSION_CALCULATOR
#define __RPN_EXPRESSION_CALCULATOR
#include <iostream>
#include "lstack.hpp"
#include "calculator.hpp"

// TODO: разделяне на HPP и CPP

class RPNExpressionCalculatorStreamBuffer : public std::streambuf {
private:
    LinkedStack<double> resultStack;
public:
    int_type overflow(int_type c) {
        if (Calculator::isdigit(c))
            resultStack.push(Calculator::digitToValue(c));
        else if (Calculator::isop(c)) {
            double rightop = resultStack.pop();
            double leftop = resultStack.pop();
            resultStack.push(Calculator::applyOperation(leftop, c, rightop));
        } else
            throw std::runtime_error("Некоректен израз: непознат символ!");
        return 0;
    }

    double getResult() const { return resultStack.peek(); }
};

class RPNExpressionCalculator : public std::ostream {
private:
    RPNExpressionCalculatorStreamBuffer sbuf;
public:
    RPNExpressionCalculator () : std::ostream(&sbuf) {}

    double getResult() const { return sbuf.getResult(); }
};

#endif