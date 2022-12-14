#ifndef __LQUEUE_HPP
#define __LQUEUE_HPP
#include <stdexcept>

#include "abstract_queue.hpp"

template <typename T>
struct QueueElement {
    T data;
    QueueElement<T>* next;
    QueueElement(T const& _data, QueueElement<T>* _next = nullptr) :
        data(_data), next(_next) {} 
};

template <typename T>
class LinkedQueue : public AbstractQueue<T> {
private:
    QueueElement<T> *front, *back;
    // инвариант на класа:
    // front == nullptr && back == nullptr || front != nullptr && back != nullptr

    void copy(LinkedQueue<T> const&);
    void erase();
public:
    LinkedQueue() : front(nullptr), back(nullptr) {}
    LinkedQueue(LinkedQueue<T> const&);
    LinkedQueue& operator=(LinkedQueue<T> const&);
    ~LinkedQueue();

    // проверява дали опашка е празна
    virtual bool empty() const { return front == nullptr; }

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
T const& LinkedQueue<T>::head() const {
    if (empty())
        throw std::runtime_error("Опит за поглеждане в празна опашка");
    return front->data;
}

template <typename T>
T& LinkedQueue<T>::head() {
    if (empty())
        throw std::runtime_error("Опит за поглеждане в празна опашка");
    return front->data;
}

template <typename T>
void LinkedQueue<T>::enqueue(T const& x) {
    QueueElement<T>* newElement = new QueueElement<T>{x};
    if (empty())
        front = newElement;
    else
        back->next = newElement;
    back = newElement;
}

template <typename T>
T LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::runtime_error("Опит за изваждане от празна опашка");
    if (front == back)
        // само 1 елемент
        back = nullptr;
    QueueElement<T>* oldElement = front;
    front = front->next;
    T result = oldElement->data;
    delete oldElement;
    return result;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T> const& other) {
    copy(other);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T> const& other) {
    if (this != &other) {
        erase();
        copy(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    erase();
}

template <typename T>
void LinkedQueue<T>::copy(LinkedQueue<T> const& other) {
    /*
    !!! 
    while (!other.empty())
        enqueue(other.dequeue());
    */
    if (other.front != nullptr) {
        // other не е празен
        back = front = new QueueElement<T>{other.front->data, nullptr};
        QueueElement<T>* nextToCopy = other.front->next;
        while (nextToCopy) {
            back = back->next = new QueueElement<T>{nextToCopy->data, nullptr};
            nextToCopy = nextToCopy->next;
        }
    } else
        front = back = nullptr;
}

template <typename T>
void LinkedQueue<T>::erase() {
    while(!empty())
        dequeue();
}

#endif