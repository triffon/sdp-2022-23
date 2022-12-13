#ifndef __LIST_HIGHORDER_TESTS
#define __LIST_HIGHORDER_TESTS

#include "doctest.h"
#include "llist.hpp"
#include "dllist.hpp"
#include "list_highorder.hpp"
#include "list_tests.hpp"
#include <cmath>

#define LHO ListHighOrder<AnyList, int>

TEST_CASE_TEMPLATE("Добавяне на 1 към всеки елемент на списъка с map",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    AnyList result = LHO::map([](auto x) -> auto { return x + 1; }, l);

    int i = 2;
    for(int x : result)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 12);
}

TEST_CASE_TEMPLATE("Добавяне на 1 към всеки елемент на списъка с mapAssign",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    LHO::mapAssign([](auto x) -> auto { return x + 1; }, l);

    int i = 2;
    for(int x : l)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 12);
}

TEST_CASE_TEMPLATE("Филтриране на нечетните елементи в списъка с filter",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    AnyList result = LHO::filter([](auto x) -> auto { return x % 2 != 0; }, l);

    int i = -1;
    for(int x : result)
        CHECK_EQ(x, i += 2);
    CHECK_EQ(i, 9);
}

TEST_CASE_TEMPLATE("Изтриване на нечетните елементи в списъка с filterAssign",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    LHO::filterAssign([](auto x) -> auto { return x % 2 != 0; }, l);

    int i = -1;
    for(int x : l)
        CHECK_EQ(x, i += 2);
    CHECK_EQ(i, 9);
}

TEST_CASE_TEMPLATE("Сума на елементите на списък чрез foldr и foldl",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    auto plus = [](auto x, auto y) -> auto { return x + y; };
    CHECK_EQ(LHO::foldr(plus, 0, l), 55);
    CHECK_EQ(LHO::foldl(plus, 0, l), 55);
}

TEST_CASE_TEMPLATE("Сумата на квадратите на нечетните елементи на списък",
                    AnyList, ALL_LISTS) {

    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    CHECK_EQ(LHO::foldr([](auto x, auto y) -> auto { return x + y; }, 0,
                        LHO::map([](auto x) -> auto { return x * x; },
                                LHO::filter([](auto x) -> auto { return x % 2 != 0; }, l))), 165);
}

// TODO: направете тестове, в които foldr и foldl дават различен резултат
#endif