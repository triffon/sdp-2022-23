#ifndef __SLIST_HPP
#define __SLIST_HPP

#include "selement.hpp"

class SList : public LinkedList<SElement*>,
              public SElement {
public:
    SList* clone() const { return new SList(*this); }

    // TODO: голяма 4

    SList& operator<<(SElement const& se) {
        LinkedList<SElement*>::insertLast(se.clone());
        return *this;
    }

    // извеждане
    void print(std::ostream& os) {
        os << '(';
        /*
        for(SElement* se : *this) {
            se->print(os);
            os << ' ';
        }
        */
        SList::I it = begin();
        if (it.valid()) {
            (*it++)->print(os);
            while(it.valid()) {
                os << ' ';
                (*it++)->print(os);
            }
        }
        os << ')';
    }

    // събиране на елемeнти
    void collect(LinkedList<int>& l) {
        for(SElement* se : *this)
            se->collect(l);
    }
};

#endif