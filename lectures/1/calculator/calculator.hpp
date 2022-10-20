#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP
#include <string>

class Calculator {
protected:
    static bool isdigit(char c);
    static bool isop(char c);
    static double digitToValue(char c);
    static double applyOperation(double left, char op, double right);
    static unsigned priority(char op);

public:
    virtual double calculate(std::string const& s) = 0;
    virtual ~Calculator() {}
};

#endif