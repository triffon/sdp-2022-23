#ifndef __STACK_HPP
#define __STACK_HPP
#include <cassert>
#include <exception>
#include "abstract_stack.hpp"

template <typename T>
class Stack : public AbstractStack<T> {
private:
    static const size_t MAXSTACK = 100;
    static const int EMPTY_STACK = -1;


    // стекът
    T stack[MAXSTACK];

    // индекс на послдния включен елемент
    int top;

    // проверка дали стек е запълнен на максимален капацитет
    bool full() const;
public:
    // създаване на празен стек
    Stack();

    // проверка за празнота
    bool empty() const;

    // включване на елемент
    void push(T const& x);

    // намиране на последния включен елемент
    T const& peek() const;

    // изключване на последния включен елемент
    T pop();
};

// създаване на празен стек
// O(1)
template <typename T>
Stack<T>::Stack() {
    top = EMPTY_STACK;
}   

// проверка за празнота
// O(1)
template <typename T>
bool Stack<T>::empty() const {
    return top == EMPTY_STACK;
}

// включване на елемент
// O(1)
template <typename T>
void Stack<T>::push(T const& x) {
    if (full())
        throw std::runtime_error("Опит за включване на елемент в пълен стек!");
    stack[++top] = x;
}

// намиране на последния включен елемент
// O(1)
template <typename T>
T const& Stack<T>::peek() const {
    if (empty())
        throw std::runtime_error("Опит за поглеждане на елемент в празен стек");    
    assert(top >= 0 && top < MAXSTACK);
    return stack[top];
}

// изключване на последния включен елемент
// O(1)
template <typename T>
T Stack<T>::pop() {
    if (empty())
        throw std::runtime_error("Опит за изключване на елемент в празен стек");    
    return stack[top--];
}

// O(1)
template <typename T>
bool Stack<T>::full() const {
    return top == MAXSTACK - 1;
}

#endif