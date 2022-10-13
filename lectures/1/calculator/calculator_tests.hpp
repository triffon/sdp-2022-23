#include "doctest.h"
#include "rpn_calculator.hpp"

TEST_CASE("Тестовият израз в обратен полски запис се пресмята коректно") {
    RPNCalculator c;
    CHECK_EQ(c.calculateFromRPN("12+345/-*"), doctest::Approx(6.6));
}