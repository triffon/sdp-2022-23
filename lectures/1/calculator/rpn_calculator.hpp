#ifndef __RPN_CALCULATOR_HPP
#define __RPN_CALCULATOR_HPP
#include <string>

class RPNCalculator {
public:
    double calculateFromRPN(std::string const& s);
};

#endif