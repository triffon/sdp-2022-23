#include "rpn_stream_calculator.hpp"

RPNStreamCalculator::RPNStreamCalculator() : converter(expressionCalculator) {}

double RPNStreamCalculator::calculate(std::string const& expr) {
    converter << expr << '=';
    return expressionCalculator.getResult();    
}
