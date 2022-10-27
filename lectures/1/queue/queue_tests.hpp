#include "doctest.h"

#include "squeue.hpp"

TYPE_TO_STRING(StaticQueue<int>);

TEST_CASE_TEMPLATE("След създаване на опашка, тя е празна",
                   AnyQueue, StaticQueue<int>) {
    AnyQueue q;
    CHECK(q.empty());
}

TEST_CASE_TEMPLATE("След добавяне на елемент в опашка, тя не е празна",
                   AnyQueue, StaticQueue<int>) {
    AnyQueue q;
    q.enqueue(42);
    CHECK_FALSE(q.empty());
}

TEST_CASE_TEMPLATE("Опит за поглеждане в или изключване на елемент от празна опашка хвърля изключение",
                   AnyQueue, StaticQueue<int>) {
    AnyQueue q;
    CHECK_THROWS(q.head());
    CHECK_THROWS(q.dequeue());
}

TEST_CASE_TEMPLATE("При последователно добавяне на елементи в опашката се изключва първият добавен",
                    AnyQueue, StaticQueue<int>) {
    AnyQueue q;
    for(int i = 1; i <= 10; i++)
        q.enqueue(i);
    CHECK_EQ(q.head(), 1);
    CHECK_EQ(q.dequeue(), 1);
    CHECK_NE(q.head(), 1);
}

TEST_CASE_TEMPLATE("При последователно добавяне на елементи в опашката, се изключват в същия ред и след това опашката остава празна",
                    AnyQueue, StaticQueue<int>) {
    AnyQueue q;
    for(int i = 1; i <= 10; i++)
        q.enqueue(i);
    CHECK_FALSE(q.empty());
    for(int i = 1; i <= 10; i++)
        CHECK_EQ(q.dequeue(), i);
    CHECK(q.empty());

    for(int i = 11; i <= 20; i++)
        q.enqueue(i);
    CHECK_FALSE(q.empty());
    for(int i = 11; i <= 20; i++)
        CHECK_EQ(q.dequeue(), i);
    CHECK(q.empty());
}