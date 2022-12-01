#ifndef __SQLIST_TESTS_HPP
#define __SQLIST_TESTS_HPP

#include "doctest.h"
#include "sqlist.hpp"
#include "simple_stack.hpp"
#include "simple_queue.hpp"

TEST_CASE("Включване на елементи в списък от един стек и една опашка") {
    StackQueueList<int> sql;
    // считаме, че списъкът притежава обектите, към които сочат указателите
    sql.insertLast(new SimpleStack<int>);
    sql.insertLast(new SimpleQueue<int>);
    for (SimpleContainer<int>* c : sql)
        for(int i = 1; i <= 10; i++)
            c->insert(i);

    typename StackQueueList<int>::I it = sql.begin();

    // първият елемент е стек
    int i = 10;
    int x;
    while ((*it)->remove(x))
        CHECK_EQ(x, i--);
    CHECK_EQ(i, 0);

    // вторият елемент е опашка
    ++it;
    i = 1;
    while ((*it)->remove(x))
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 11);
}

#endif