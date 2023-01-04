#ifndef __QUEUE_UTILS_TEST_HPP
#define __QUEUE_UTILS_TEST_HPP

#include "doctest.h"
#include "squeue.hpp"
#include "lqueue.hpp"
#include "queue_utils.hpp"
#define ALL_QUEUES StaticQueue<int>, LinkedQueue<int>

TEST_CASE_TEMPLATE("От тестова опашка коректно се изключва най-малкия елемент",
                   AnyQueue, ALL_QUEUES) {
    AnyQueue q;
    q.enqueue(5);
    q.enqueue(3);
    q.enqueue(6);
    q.enqueue(1);
    q.enqueue(2);
    CHECK_EQ(QueueUtils<int>::extractMin(q), 1);
    while(!q.empty()) {
        int x = q.dequeue();
        // TODO: да се подобри!
        CHECK((x == 2 || x == 3 || x == 5 || x == 6));
    }
} 

TEST_CASE_TEMPLATE("Тестова опашка се сортира успешно",
                    AnyQueue, ALL_QUEUES) {
    AnyQueue q;
    q.enqueue(5);
    q.enqueue(3);
    q.enqueue(6);
    q.enqueue(1);
    q.enqueue(2);
    int expectedResult[] = {1, 2, 3, 5, 6};
    AnyQueue sortedQueue;
    QueueUtils<int>::sortQueue(q, sortedQueue);
    int i = 0;
    while (!sortedQueue.empty())
        CHECK_EQ(expectedResult[i++], sortedQueue.dequeue());
    CHECK_EQ(i, 5);
}

#endif