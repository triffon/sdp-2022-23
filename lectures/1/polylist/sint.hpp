#ifndef __SINT_HPP
#define __SINT_HPP

#include "selement.hpp"

class SInt : public SElement {
private:
    int data;
public:
    SInt* clone() const { return new SInt(*this); }

    SInt(int _data = 0) : data(_data) {}

    // извеждане
    void print(std::ostream& os) {
        os << data;
    }

    // събиране на елемeнти
    void collect(LinkedList<int>& l) {
        l.insertLast(data);
    }
};

#endif