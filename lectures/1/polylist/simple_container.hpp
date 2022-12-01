#ifndef __SIMPLE_CONTAINER_HPP
#define __SIMPLE_CONTAINER_HPP

template <typename T>
class SimpleContainer {
public:
    // включва елемент в контейнера
    virtual void insert(T const&) = 0;

    // изключва елемент от контейнера
    virtual bool remove(T&) = 0;

    virtual ~SimpleContainer() {}
};

#endif