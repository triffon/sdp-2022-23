#include "rpn_direct_calculator.hpp"

void RPNDirectCalculator::processOperation(char op) {
    double rightop = resultStack.pop();
    double leftop = resultStack.pop();
    resultStack.push(applyOperation(leftop, op, rightop));
}

double RPNDirectCalculator::calculate(std::string const& expr) {
    for(char c : expr) {
        if (isdigit(c))
            resultStack.push(digitToValue(c));
        else if (isop(c) || c == '(') {
            char op;
            while (!operationStack.empty() &&
                   operationStack.peek() != '(' &&
                   priority(operationStack.peek()) >= priority(c))
                processOperation(operationStack.pop());
            operationStack.push(c);
        }
        else if (c == ')') {
            char op;
            while ((op = operationStack.pop()) != '(')
                processOperation(op);
        } else 
            throw std::runtime_error("Некоректен израз: непознат символ!");
    }
    while (!operationStack.empty())
        processOperation(operationStack.pop());
    
    double result = resultStack.pop();
    if (!resultStack.empty())
        throw std::runtime_error("Некоректен израз: повече цифри от операции!");
    return result;
}