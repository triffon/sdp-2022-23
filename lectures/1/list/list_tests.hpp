#include "doctest.h"
#include "llist.hpp"

TYPE_TO_STRING(LinkedList<int>);
#define ALL_LISTS LinkedList<int>

TEST_CASE_TEMPLATE("При създаване на списък той е празен",
                    AnyList, ALL_LISTS) {
    AnyList l;
    CHECK(l.empty());
}