#ifndef __RPN_STREAM_CALCULATOR
#define __RPN_STREAM_CALCULATOR
#include "rpn_converter.hpp"
#include "rpn_expression_calculator.hpp"
#include "calculator.hpp"

class RPNStreamCalculator : public Calculator {
    RPNConverter converter;
    RPNExpressionCalculator expressionCalculator;
public:
    RPNStreamCalculator();
    double calculate(std::string const& expr);
};

#endif