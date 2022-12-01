#ifndef __SQLIST_TESTS_HPP
#define __SQLIST_TESTS_HPP

#include "doctest.h"
#include "sqlist.hpp"
#include "simple_stack.hpp"
#include "simple_queue.hpp"

TEST_CASE("Включване на елементи в списък от един стек и една опашка") {
    SimpleStack<int> stack;
    SimpleQueue<int> queue;
    StackQueueList<int> sql;

    sql.insertLast(&stack);
    sql.insertLast(&queue);

    for (SimpleContainer<int>* c : sql)
        for(int i = 1; i <= 10; i++)
            c->insert(i);
    
    int i = 10;
    while (!stack.empty())
        CHECK_EQ(stack.pop(), i--);
    CHECK_EQ(i, 0);

    i = 1;
    while (!queue.empty())
        CHECK_EQ(queue.dequeue(), i++);
    CHECK_EQ(i, 11);
}

#endif