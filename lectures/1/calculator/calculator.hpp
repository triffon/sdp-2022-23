#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP
#include <string>

class Calculator {
public:
    virtual double calculate(std::string const& s) = 0;
    virtual ~Calculator() {}
};

#endif