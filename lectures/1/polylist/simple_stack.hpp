#ifndef __SIMPLE_STACK_HPP
#define __SIMPLE_STACK_HPP

#include "lstack.hpp"
#include "simple_container.hpp"

template <typename T>
class SimpleStack : public LinkedStack<T>,
                    public SimpleContainer<T> {
public:
    // включва елемент в контейнера
    void insert(T const& x) {
        LinkedStack<T>::push(x);
    }

    // изключва елемент от контейнера
    bool remove(T& x) {
        if (LinkedStack<T>::empty())
            return false;
        x = LinkedStack<T>::peek();
        LinkedStack<T>::pop();
        return true;
    }

};

#endif