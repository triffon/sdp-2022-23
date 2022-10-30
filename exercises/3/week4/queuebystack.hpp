#ifndef __QBYSTACK_HPP
#define __QBYSTACK_HPP
#include <iostream>

#include "stack/lstack.hpp"

template <typename T>
class QueueByStacks
{
private:
    LinkedStack<T> pushingStack;
    LinkedStack<T> poppingStack;

public:
    bool empty() const;
    void push(T const &x);
    T const &peek();
    T pop();

private:
    void assureElementsInPoppingStack();
    void transferToPoppingStack();
};

template <typename T>
bool QueueByStacks<T>::empty() const
{
    return pushingStack.empty() && poppingStack.empty();
}

template <typename T>
void QueueByStacks<T>::push(T const &x)
{
    pushingStack.push(x);
}

template <typename T>
T const &QueueByStacks<T>::peek()
{
    assureElementsInPoppingStack();
    return poppingStack.peek();
}

template <typename T>
T QueueByStacks<T>::pop()
{
    assureElementsInPoppingStack();
    return poppingStack.pop();
}

template <typename T>
void QueueByStacks<T>::assureElementsInPoppingStack()
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty");
    }
    if (!poppingStack.empty())
    {
        return;
    }
    transferToPoppingStack();
}

template <typename T>
void QueueByStacks<T>::transferToPoppingStack()
{
    while (!pushingStack.empty())
    {
        poppingStack.push(pushingStack.pop());
    }
}

#endif