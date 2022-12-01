#ifndef __SQLIST_HPP
#define __SQLIST_HPP

#include "simple_container.hpp"
#include "llist.hpp"

template<typename T>
using StackQueueList = LinkedList<SimpleContainer<T>*>;

#endif