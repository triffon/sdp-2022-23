#ifndef __ABSTRACT_QUEUE_HPP
#define __ABSTRACT_QUEUE_HPP

template <typename T>
class AbstractQueue {
public:
    // проверява дали опашка е празна
    virtual bool empty() const = 0;

    // включване на елемент в края на опашката
    virtual void enqueue(T const&) = 0;

    // изключване на елемента в началото на опашката
    virtual T dequeue() = 0;

    // поглеждане на елемента в началото на опашката
    virtual T const& head() const = 0;

    // поглеждане на елемента в началото на опашката с възможност за промяна
    virtual T& head() = 0;

    virtual ~AbstractQueue() {}
};

#endif