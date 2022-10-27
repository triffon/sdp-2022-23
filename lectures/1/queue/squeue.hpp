#ifndef __SQUEUE_HPP
#define __SQUEUE_HPP
#include <cstddef>
#include <stdexcept>
#include "abstract_queue.hpp"

template <typename T>
class StaticQueue : public AbstractQueue<T> {
private:
    static const size_t SIZE = 100;
    T queue[SIZE];
    int front, back;

    bool full() const { return (back + 2) % SIZE == front; }
public:
    // създава празна опашка
    StaticQueue() : front(0), back(-1) {}

    // проверява дали опашка е празна
    virtual bool empty() const { return (back + 1) % SIZE == front; }

    // включване на елемент в края на опашката
    virtual void enqueue(T const&);

    // изключване на елемента в началото на опашката
    virtual T dequeue();

    // поглеждане на елемента в началото на опашката
    virtual T const& head() const;

    // поглеждане на елемента в началото на опашката с възможност за промяна
    virtual T& head();
};

template <typename T>
T StaticQueue<T>::dequeue() {
    if (empty())
        throw std::runtime_error("Опит за изваждане от празна опашка");
    T result = queue[front];
    ++front %= SIZE;
    return result;
}

template <typename T>
void StaticQueue<T>::enqueue(T const& x) {
    if (full())
        throw std::runtime_error("Надвишаване на капацитета при опит за включване на елемент");
    queue[++back %= SIZE] = x;    
}

template <typename T>
T const& StaticQueue<T>::head() const {
    if (empty())
        throw std::runtime_error("Опит за поглеждане в празна опашка");
    return queue[front];
}

template <typename T>
T& StaticQueue<T>::head() {
    if (empty())
        throw std::runtime_error("Опит за поглеждане в празна опашка");
    return queue[front];
}

#endif