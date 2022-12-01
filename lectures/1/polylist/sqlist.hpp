#ifndef __SQLIST_HPP
#define __SQLIST_HPP

#include "simple_container.hpp"
#include "llist.hpp"

template<typename T>
class StackQueueList : public LinkedList<SimpleContainer<T>*> {
public:
    // TODO: да се реализират другите елементи на голямата 4
    ~StackQueueList() {
        for(SimpleContainer<T>* c : *this)
            delete c;
    }
};

#endif