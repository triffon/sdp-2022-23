#ifndef __LSTACK_HPP
#define __LSTACK_HPP
#include <cassert>
#include <cstddef>
#include <iostream>

#include "abstract_stack.hpp"

template <typename T>
struct StackElement {
    T data;
    StackElement<T>* next;
};

template <typename T>
class LinkedStack : public AbstractStack<T> {
private:
    // указател към двойната кутия, която е връх на стека
    StackElement<T>* top;

    // копиране на стек
    void copyStack(LinkedStack const&);

    // изтриване на стек
    void erase();

public:
    // създаване на празен стек
    LinkedStack();

    // конструктор за копиране
    LinkedStack(LinkedStack const&);

    // операция за присвояване
    LinkedStack& operator=(LinkedStack const&);

    // конструктор за преместване
    LinkedStack(LinkedStack&&);

    // операция за преместване
    LinkedStack& operator=(LinkedStack&&);

    // деструктор
    ~LinkedStack();

    // проверка за празнота
    bool empty() const;

    // включване на елемент
    void push(T const& x);

    // намиране на последния включен елемент
    T const& peek() const;

    // безопасно намиране на последния включен елемент с индикация за успех
    bool peek(T&) const;


    // изключване на последния включен елемент
    T pop();

    // изключване на последния включен елемент с код за грешка
    T pop(bool& success);

    void steal(LinkedStack&& other) {
        if (top != nullptr)
            //erase();
            throw std::runtime_error("Кражба от непразен обект!");
        top = other.top;
        other.top = nullptr;
    }
};


// създаване на празен стек
// O(1)
template <typename T>
LinkedStack<T>::LinkedStack() : top(nullptr) {}

// копиране на стек
template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack const& other) : top(nullptr) {
    std::clog << "Копиране на LinkedStack" << std::endl;
    copyStack(other);
}

// деструктор
template <typename T>
LinkedStack<T>::~LinkedStack() {
    erase();
}

template <typename T>
void LinkedStack<T>::erase() {
    // !!! delete top;
    while (!empty()) pop();
    // домашно: реализирайте го директно с представянето
}

template <typename T>
void LinkedStack<T>::copyStack(LinkedStack const& other) {
    if (other.top != nullptr) {
        // other не е празен
        StackElement<T>* lastAdded = top = new StackElement<T>{other.top->data, nullptr};
        StackElement<T>* nextToCopy = other.top->next;
        while (nextToCopy) {
            lastAdded = lastAdded->next = new StackElement<T>{nextToCopy->data, nullptr};
            nextToCopy = nextToCopy->next;
        }
    }
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack const& other) {
    std::clog << "Присвояване на LinkedStack" << std::endl;
    if (this != &other) {
        erase();
        copyStack(other);
    }
    return *this;
}


// проверка за празнота
// O(1)
template <typename T>
bool LinkedStack<T>::empty() const {
    return top == nullptr;
}

// включване на елемент
// O(1)
template <typename T>
void LinkedStack<T>::push(T const& x) {
    top = new StackElement<T>{x, top};
}

// поглеждане на последния включен елемент
// O(1)
template <typename T>
T const& LinkedStack<T>::peek() const {
    if (empty())
        throw std::runtime_error("Опит за поглеждане на елемент в празен стек");    
   return top->data;
}

// поглеждане на последния включен елемент
// O(1)
template <typename T>
bool LinkedStack<T>::peek(T& result) const {
    if (empty())
        return false;
    result = top->data;
    return true;
}

// изключване на последния включен елемент
// O(1)
template <typename T>
T LinkedStack<T>::pop() {
    if (empty())
        throw std::runtime_error("Опит за изключване на елемент в празен стек");    
    StackElement<T>* newtop = top->next;
    T x = top->data;
    delete top;
    top = newtop;
    return x;
}

// изключване на последния включен елемент
// O(1)
template <typename T>
T LinkedStack<T>::pop(bool& success) {
    if (empty()) {
        success = false;
        return T();
    }
    success = true;
    return pop();
}

// O(1)
template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack&& other) : top(other.top) {
    std::clog << "Конструктор за преместване на LinkedStack" << std::endl;
    other.top = nullptr;
}

// 
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack&& other) {
    std::cout << "Операция за преместване на LinkedStack" << std::endl;
    if (this != &other) {
        erase();
        top = other.top;
        other.top = nullptr;
    }
    return *this;
}

#endif