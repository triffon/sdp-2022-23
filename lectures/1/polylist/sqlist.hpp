#ifndef __SQLIST_HPP
#define __SQLIST_HPP

#include "simple_container.hpp"
#include "llist.hpp"

template<typename T>
class StackQueueList : public LinkedList<SimpleContainer<T>*> {
private:
    void Copy(StackQueueList const& other){
        for(SimpleContainer<T>* c : *other){
            SimpleContainer<T>* copy(c);
            append(copy);
        }
    }
public:
    StackQueueList() :  LinkedList() {}

    StackQueueList(StackQueueList const& other) {
        this->Copy(other);
    }

    StackQueueList& operator=(StackQueueList const& other) {
        if(this!=&other){
            this->erase();
            //Това би трябвало да се погрижи и за конейнерите вътре, тъй като извиква delete на пойнтъра,
            //т.е. ще извика деструктор към това, към което те сочат
            this->Copy(other);
        }
    }

    ~StackQueueList() {
        for(SimpleContainer<T>* c : *this)
            delete c;
        //this->erase()?
    }
};

#endif