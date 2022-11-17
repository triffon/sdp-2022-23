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
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка от началото и обхождането му",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        l.insertFirst(i);
    
    int i = 10;
    for(int x : l)
        CHECK_EQ(i--, x);
    CHECK_EQ(i, 0);
}

TEST_CASE_TEMPLATE("Включване на елементи на четни позиции",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i += 2)
        l.insertLast(i);
    
    // TODO: it += 2;
    for(typename AnyList::I it = l.begin(); it != l.end(); ++it, ++it)
        l.insertAfter(*it + 1, it);

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);    
}

TEST_CASE_TEMPLATE("Включване на елементи на нечетни позиции",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 2; i <= 10; i += 2)
        l.insertLast(i);
    
    // TODO: it += 2;
    for(typename AnyList::I it = l.begin(); it != l.end(); ++it)
        l.insertBefore(*it - 1, it);

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);    
}

TEST_CASE_TEMPLATE("Изключване на елементи на четни позиции с deleteAfter",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i ++)
        l.insertLast(i);
    
    int x;
    int i = 2;

    for(typename AnyList::I it = l.begin(); it != l.end(); i += 2, ++it) {
        l.deleteAfter(x, it);
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 12);

    i = -1;
    for(int x : l)
        CHECK_EQ(i += 2, x);
    CHECK_EQ(i, 9);    
}

TEST_CASE_TEMPLATE("Последователно изтриване на последния елемент в списъка",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        l.insertLast(i);
    
    int x;
    for(int i = 10; i >= 1; i--) {
        l.deleteLast(x);
        CHECK_EQ(x, i);
    }
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("Последователно изтриване на първия елемент в списъка",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        l.insertLast(i);
    
    int x;
    for(int i = 1; i <= 10; i++) {
        l.deleteFirst(x);
        CHECK_EQ(x, i);
    }
    CHECK(l.empty());
}



TEST_CASE_TEMPLATE("Изключване на елементи на четни позиции с deleteAt",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i ++)
        l.insertLast(i);

    int x;
    int i = 2;

    for(typename AnyList::I it = l.begin().next(); it != l.end(); i += 2, it.valid() ? ++it : it) {
        typename AnyList::I toDelete = it++;
        l.deleteAt(x, toDelete);
        CHECK(!toDelete.valid());
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 12);

    i = -1;
    for(int x : l)
        CHECK_EQ(i += 2, x);
    CHECK_EQ(i, 9);
}