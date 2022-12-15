#ifndef __RSTACK_HPP
#define __RSTACK_HPP
#include <cstddef>
#include <cassert>
#include <iostream>
#include <exception>
#include "abstract_stack.hpp"

template <typename T>
class ResizingStack : public AbstractStack<T> {
private:
    static const int EMPTY_STACK = -1;
    static const size_t INITSTACK = 10;

    // указател към масива на стека
    T* stack;

    // индекс на послдния включен елемент
    int top;

    // капацитет на стека
    size_t capacity;

    // проверка дали стек е запълнен на максимален капацитет
    bool full() const;

    // разширяване на стека
    void resize();

    // копиране на стека
    void copyData(ResizingStack const&);
public:
    // създаване на празен стек
    ResizingStack();

    // конструктор за копиране
    ResizingStack(ResizingStack const&);

    // операция за присвояване
    ResizingStack& operator=(ResizingStack const&);

    // деструктор
    ~ResizingStack();

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
ResizingStack<T>::ResizingStack() : capacity(INITSTACK), top(EMPTY_STACK) {
    // заделяме първоначален размер
    stack = new T[capacity];
}

// O(n)
template <typename T>
ResizingStack<T>::ResizingStack(ResizingStack const& other)
  : top(other.top), capacity(other.capacity) {
    copyData(other);
}

// O(1)
template <typename T>
ResizingStack<T>::~ResizingStack() {
    delete[] stack;
}

// O(n)
template <typename T>
void ResizingStack<T>::copyData(ResizingStack const& other) {
    stack = new T[capacity];
    for(int i = 0; i <= top; i++)
        stack[i] = other.stack[i];
}

// O(n)
template <typename T>
ResizingStack<T>& ResizingStack<T>::operator=(ResizingStack const& other) {
    if (this != &other) {
        delete[] stack;
        top = other.top;
        capacity = other.capacity;
        copyData(other);
    }
    return *this;
}

// проверка за празнота
// O(1)
template <typename T>
bool ResizingStack<T>::empty() const {
    return top == EMPTY_STACK;
}

// включване на елемент
// амортизирана: O(1)
// песимистична: O(n)
template <typename T>
void ResizingStack<T>::push(T const& x) {
    if (full())
        resize();
    stack[++top] = x;
}

// намиране на последния включен елемент
// O(1)
template <typename T>
T const& ResizingStack<T>::peek() const {
    if (empty())
        throw std::runtime_error("Опит за поглеждане на елемент в празен стек");    
    assert(top >= 0 && top < capacity);
    return stack[top];
}

// изключване на последния включен елемент
// O(1)
template <typename T>
T ResizingStack<T>::pop() {
    if (empty())
        throw std::runtime_error("Опит за изключване на елемент в празен стек");    
    return stack[top--];
}

// O(1)
template <typename T>
bool ResizingStack<T>::full() const {
    return top == capacity - 1;
}

// O(n)
template <typename T>
void ResizingStack<T>::resize() {
    // разчитаме, че викаме resize само когато стекът е пълен
    size_t newcapacity = 2 * capacity;
    std::clog << "Разширяваме стека до " << newcapacity << std::endl;
    T* newstack = new T[newcapacity];
    for(int i = 0; i < capacity; i++)
        newstack[i] = stack[i];
    capacity = newcapacity;
    delete[] stack;
    stack = newstack;
}

#endif