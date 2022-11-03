#include "doctest.h"

#include "squeue.hpp"
#include "lqueue.hpp"

TYPE_TO_STRING(StaticQueue<int>);
TYPE_TO_STRING(LinkedQueue<int>);

TEST_CASE_TEMPLATE("След създаване на опашка, тя е празна",
                   AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q;
    CHECK(q.empty());
}

TEST_CASE_TEMPLATE("След добавяне на елемент в опашка, тя не е празна",
                   AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q;
    q.enqueue(42);
    CHECK_FALSE(q.empty());
}

TEST_CASE_TEMPLATE("Опит за поглеждане в или изключване на елемент от празна опашка хвърля изключение",
                   AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q;
    CHECK_THROWS(q.head());
    CHECK_THROWS(q.dequeue());
}

TEST_CASE_TEMPLATE("При последователно добавяне на елементи в опашката се изключва първият добавен",
                    AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q;
    for(int i = 1; i <= 10; i++)
        q.enqueue(i);
    CHECK_EQ(q.head(), 1);
    CHECK_EQ(q.dequeue(), 1);
    CHECK_NE(q.head(), 1);
}

TEST_CASE_TEMPLATE("При последователно добавяне на елементи в опашката, се изключват в същия ред и след това опашката остава празна",
                    AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
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

TEST_CASE_TEMPLATE("Многократно добавяне и изключване на елементи",
                    AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q;
    for(int j = 0; j < 100; j++) {
        for(int i = 1; i <= 10; i++)
            q.enqueue(i);
        CHECK_FALSE(q.empty());
        for(int i = 1; i <= 10; i++)
            CHECK_EQ(q.dequeue(), i);
        CHECK(q.empty());
    }
}


TEST_CASE_TEMPLATE("Конструкторът за копиране не споделя памет",
                    AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q1;
    for(int i = 1; i <= 10; i++)
        q1.enqueue(i);
    AnyQueue q2 = q1;
//    std::clog << s2.pop() << std::endl;
    q2.enqueue(20);
    for(int i = 1; i <= 10; i++) {
        CHECK(! q1.empty());
        CHECK_EQ(q1.dequeue(), i);
    }
    CHECK(q1.empty());
}

TEST_CASE_TEMPLATE("Копиране на празна опашка",
                    AnyQueue, StaticQueue<int>, LinkedQueue<int>) {
    AnyQueue q1;
    AnyQueue q2 = q1;
    CHECK(q2.empty());
}

// TODO: тест за операция за присвояване