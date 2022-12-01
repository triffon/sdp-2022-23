#ifndef __SELEMENT_HPP
#define __SELEMENT_HPP

#include <iostream>
#include "llist.hpp"

class SElement {
public:
    virtual SElement* clone() const = 0;

    // извеждане
    virtual void print(std::ostream& = std::cout) = 0;

    // събиране на елемeнти
    virtual void collect(LinkedList<int>&) = 0;

    ~SElement() {}
};

#endif