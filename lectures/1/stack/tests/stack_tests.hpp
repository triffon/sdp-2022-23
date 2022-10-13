#include "doctest.h"
#include "../stack.hpp"
#include "../rstack.hpp"
#include "../lstack.hpp"

TYPE_TO_STRING(Stack<int>);
TYPE_TO_STRING(ResizingStack<int>);
TYPE_TO_STRING(LinkedStack<int>);

TEST_CASE_TEMPLATE("След създаване на стек той е празен",
                    TestStack, Stack<int>, ResizingStack<int>, LinkedStack<int>) {
    TestStack s;
    CHECK(s.empty());
}

TEST_CASE_TEMPLATE("Стекът не е празен след добавяне",
                    TestStack, Stack<int>, ResizingStack<int>, LinkedStack<int>) {
    TestStack s;
    s.push(10);
    CHECK(!s.empty());
}

TEST_CASE_TEMPLATE("Елементите се изключват в ред обратен на включване",
                    TestStack, Stack<int>, ResizingStack<int>, LinkedStack<int>) {
    TestStack s;
    s.push(10); s.push(20); s.push(30);
    CHECK( !s.empty() );
    CHECK_EQ( s.pop(), 30);
    CHECK_EQ( s.pop(), 20);
    CHECK_EQ( s.pop(), 10);
    CHECK( s.empty() );
}

TEST_CASE_TEMPLATE("Peek връща последно включения елемент",
                    TestStack, Stack<int>, ResizingStack<int>, LinkedStack<int>) {
    TestStack s;
    s.push(10);
    CHECK_EQ( s.peek(), 10);
    s.push(20);
    CHECK_EQ( s.peek(), 20);
    s.pop();
    CHECK_EQ( s.peek(), 10);
}

TEST_CASE("LinkedStack: неуспех при опит за поглеждане в празен стек") {
    LinkedStack<int> s;
    int x;
    CHECK( ! s.peek(x) );
}

TEST_CASE_TEMPLATE("Изключение при опит за поглеждане в или изключване от празен стек",
                    TestStack, Stack<int>, ResizingStack<int>, LinkedStack<int>) {
    TestStack s;
    CHECK_THROWS_AS( s.peek(), std::runtime_error );
    CHECK_THROWS_AS( s.pop(), std::runtime_error );
}

TEST_CASE("LinkedStack: безопасният peek връща последно включения елемент") {
    LinkedStack<int> s;
    s.push(10);
    int x;
    CHECK( s.peek(x));
    CHECK_EQ( x, 10 );
    s.push(20);
    CHECK( s.peek(x));
    CHECK_EQ( x, 20 );
    s.pop();
    CHECK( s.peek(x));
    CHECK_EQ( x, 10 );
}

TEST_CASE("LinkedStack: конструкторът за копиране не споделя памет") {
    LinkedStack<int> s1;
    for(int i = 1; i <= 10; i++)
        s1.push(i);
    LinkedStack<int> s2 = s1;
    std::clog << s2.pop() << std::endl;
    s2.push(20);
    for(int i = 10; i >= 1; i--) {
        CHECK(! s1.empty());
        CHECK_EQ(s1.pop(), i);
    }
    CHECK(s1.empty());
}

TEST_CASE("LinkedStack: безопасният pop връща грешка при опит за изключване от празен стек") {
    LinkedStack<int> s;
    bool success = true;
    int x = s.pop(success);
    CHECK_FALSE( success );
}

template <typename T>
LinkedStack<T> reverse(LinkedStack<T> s) {
    LinkedStack<T> result;
    while (!s.empty())
        result.push(s.pop());
    return result;
}

LinkedStack<int> createStack(unsigned n) {
    LinkedStack<int> result;
    for(int i = 1; i <= n; i++)
        result.push(i);
    return result;
}

LinkedStack<int> doubleTop(LinkedStack<int> s) {
    s.push(s.pop() * 2);
    return s;
}

TEST_CASE("LinkedStack: копиране при reverse") {
    std::clog << "LinkedStack: копиране при reverse\n";
    LinkedStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    LinkedStack<int> s2 = reverse(s);
    CHECK_EQ(s2.pop(), 1);
    CHECK_EQ(s2.pop(), 2);
    CHECK_EQ(s2.pop(), 3);
    CHECK(s2.empty());
}

TEST_CASE("LinkedStack: копиране при doubleTop") {
    std::clog << "LinkedStack: копиране при doubleTop\n";
    LinkedStack<int> s2 = doubleTop(createStack(10));
}

TEST_CASE("LinkedStack: присвояване при doubleTop") {
    std::clog << "LinkedStack: присвояване при doubleTop\n";
    LinkedStack<int> s2 = createStack(10);
    s2 = doubleTop(createStack(10));
}

TEST_CASE("LinkedStack: std::move") {
    std::clog << "LinkedStack: std::move\n";
    LinkedStack<int> temp = createStack(10);
    LinkedStack<int> s2 = doubleTop(std::move(temp));
    CHECK(temp.empty());
}
