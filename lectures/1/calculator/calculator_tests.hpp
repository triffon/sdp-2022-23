#include "doctest.h"
#include "rpn_calculator.hpp"

TEST_CASE("Тестовият израз в обратен полски запис се пресмята коректно") {
    RPNCalculator c;
    CHECK_EQ(c.calculateFromRPN("12+345/-*"), doctest::Approx(6.6));
}

TEST_CASE("При некоректен израз в обратен полски запис се хвърля изключение") {
    RPNCalculator c;
    CHECK_THROWS(c.calculateFromRPN("1z+345/-*"));
}

TEST_CASE("При опит за деление на 0 се хвърля изключение") {
    RPNCalculator c;
    CHECK_THROWS(c.calculateFromRPN("30/"));
}

TEST_CASE("При подаване на празен низ се хвърля изключение") {
    RPNCalculator c;
    CHECK_THROWS(c.calculateFromRPN(""));
}

TEST_CASE("При повече цифри отколкото операции се хвърля изключение") {
    RPNCalculator c;
    CHECK_THROWS(c.calculateFromRPN("351+"));
}

TEST_CASE("При повече операции отколкото налични аргументи се хвърля изключение") {
    RPNCalculator c;
    CHECK_THROWS(c.calculateFromRPN("35+2*-"));
}

TEST_CASE("При 0 операции се връща единствената цифра") {
    RPNCalculator c;
    CHECK_EQ(c.calculateFromRPN("3"), 3);
}