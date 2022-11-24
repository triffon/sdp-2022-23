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

    AnyList result = LHO::map(LHO::plus1, l);

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

    LHO::mapAssign(LHO::plus1, l);

    int i = 2;
    for(int x : l)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 12);
}
#endif