#include "doctest.h"
#include "llist.hpp"

TYPE_TO_STRING(LinkedList<int>);
#define ALL_LISTS LinkedList<int>

TEST_CASE_TEMPLATE("При създаване на списък той е празен",
                    AnyList, ALL_LISTS) {
    AnyList l;
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("При добавяне на елемент в списък той вече не е празен",
                    AnyList, ALL_LISTS) {
    AnyList l;
    l.insertLast(42);
    CHECK(!l.empty());
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка и обхождането му",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        l.insertLast(i);
    
    int i = 1;
    //for(int x : l)
    for(typename AnyList::I it = l.begin(); it != l.end(); ++it) {
        int x = *it;
        CHECK_EQ(i++, x);
    }
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка от началото и обхождането му",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        l.insertFirst(i);
    
    int i = 10;
    //for(int x : l)
    for(typename AnyList::I it = l.begin(); it != l.end(); ++it) {
        int x = *it;
        CHECK_EQ(i--, x);
    }
    CHECK_EQ(i, 0);
}

// TODO: тест за insertBefore