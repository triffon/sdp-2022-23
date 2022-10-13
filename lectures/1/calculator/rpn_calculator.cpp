#include "rpn_calculator.hpp"

bool RPNCalculator::isdigit(char c) {
    return '0' <= c && c <= '9';
}

bool RPNCalculator::isop(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double RPNCalculator::digitToValue(char digit) {
    return digit - '0';
}

unsigned RPNCalculator::priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 1000;
        default:
            return 0; 
    }
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

double RPNCalculator::calculate(std::string const& expr) {
    return calculateFromRPN(toRPN(expr));
}

std::string RPNCalculator::toRPN(std::string const& expr) {
    std::string result;
    for(char c : expr) {
        if (isdigit(c))
            result += c;
        else if (isop(c) || c == '(') {
            char op;
            while (!operationStack.empty() &&
                   operationStack.peek() != '(' &&
                   priority(operationStack.peek()) >= priority(c))
                result += operationStack.pop();
            operationStack.push(c);
        }
        else if (c == ')') {
            char op;
            while ((op = operationStack.pop()) != '(')
                result += op;
        } else 
            throw std::runtime_error("Некоректен израз: непознат символ!");
    }
    while (!operationStack.empty())
        result += operationStack.pop();
    return result;
}