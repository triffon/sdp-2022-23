#include "rpn_calculator.hpp"

bool RPNCalculator::isdigit(char c) {
    return '0' <= c && c <= '9';
}

bool RPNCalculator::isop(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double RPNCalculator::digitToValue(char c) {
    return c - '0';
}

double RPNCalculator::applyOperation(double left, char op, double right) {
    switch(op) {
        case '+' : return left + right;
        case '-' : return left - right;
        case '*' : return left * right;
        case '/' :
                if (right == 0)
                    throw std::runtime_error("Опит за деление на 0!");
                return left / right;
        default  : assert(isop(op)); return 0;
    }
}

double RPNCalculator::calculateFromRPN(std::string const& expr) {
    for(char c : expr) {
        if (isdigit(c))
            resultStack.push(digitToValue(c));
        else if (isop(c)) {
            double rightop = resultStack.pop();
            double leftop = resultStack.pop();
            resultStack.push(applyOperation(leftop, c, rightop));
        } else
            throw std::runtime_error("Некоректен израз: непознат символ!");
    }
    double result = resultStack.pop();
    if (!resultStack.empty())
        throw std::runtime_error("Некоректен израз: повече цифри от операции!");
    return result;
}

double RPNCalculator::calculate(std::string const& s) {
    return calculateFromRPN(toRPN(s));
}

std::string RPNCalculator::toRPN(std::string const& s) {
    return "";
}