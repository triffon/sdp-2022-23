#ifndef __SIMPLE_QUEUE_HPP
#define __SIMPLE_QUEUE_HPP

#include "lqueue.hpp"
#include "simple_container.hpp"

template <typename T>
class SimpleQueue : public LinkedQueue<T>, 
                    public SimpleContainer<T> {
public:
    // включва елемент в контейнера
    void insert(T const& x) {
        LinkedQueue<T>::enqueue(x);
    }

    // изключва елемент от контейнера
    bool remove(T& x) {
        if (LinkedQueue<T>::empty())
            return false;
        x = LinkedQueue<T>::head();
        LinkedQueue<T>::dequeue();
        return true;
    }

};

#endif