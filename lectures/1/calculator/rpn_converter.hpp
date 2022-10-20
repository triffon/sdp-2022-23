#ifndef __RPN_CONVERTER
#define __RPN_CONVERTER
#include <iostream>
#include "calculator.hpp"
#include "lstack.hpp"

// TODO: разделяне на HPP и CPP

class RPNConverterStreamBuffer : public std::streambuf {
private:
    std::ostream& os;
    LinkedStack<char> operationStack;

public:
    RPNConverterStreamBuffer(std::ostream& _os) : os(_os) {}

    int_type overflow(int_type c) {
        // TODO: използване на EOF вместо =
        if (c == '=') {
            while (!operationStack.empty())
                os.put(operationStack.pop());
        } else if (Calculator::isdigit(c))
            os.put(c);
        else if (Calculator::isop(c) || c == '(') {
            char op;
            while (!operationStack.empty() &&
                   operationStack.peek() != '(' &&
                   Calculator::priority(operationStack.peek()) >= Calculator::priority(c))
                os.put(operationStack.pop());
            operationStack.push(c);
        }
        else if (c == ')') {
            char op;
            while ((op = operationStack.pop()) != '(')
                os.put(op);
        } else 
            throw std::runtime_error("Некоректен израз: непознат символ!");
        return 0;
    }
};

class RPNConverter : public std::ostream {
private:
    RPNConverterStreamBuffer sbuf;
public:
    RPNConverter(std::ostream& os = std::cout) : sbuf(os), std::ostream(&sbuf) {}
};

#endif