#include <stdexcept>
#include <cassert>
#include "calculator.hpp"

bool Calculator::isdigit(char c) {
    return '0' <= c && c <= '9';
}

bool Calculator::isop(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double Calculator::digitToValue(char digit) {
    return digit - '0';
}

unsigned Calculator::priority(char op) {
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

double Calculator::applyOperation(double left, char op, double right) {
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
