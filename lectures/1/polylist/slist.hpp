#ifndef __SLIST_HPP
#define __SLIST_HPP

#include "selement.hpp"

class SList : public LinkedList<SElement*>,
              public SElement {
private:
    void cloneAll() {
        for(SElement*& se : *this)
            se = se->clone();
    }

    void deleteAll() {
        /*
            for (T x : l) ...
            for (T const& x : l) ...
            for (T& x : l)
        */
        for(SElement* se : *this)
            delete se;
    }

public:
    SList* clone() const { return new SList(*this); }

    SList() {}

    SList(SList const& other) : LinkedList<SElement*>(other) {
        std::clog << "Клонираме списък: ";
        print(std::clog);
        std::clog << std::endl;
        cloneAll();
    }

    SList& operator=(SList const& other) {
        if (this != &other) {
            deleteAll();
            LinkedList<SElement*>::operator=(other);
            cloneAll();
        }
        return *this;
    }

    ~SList() {
        deleteAll();
    }

    SList& operator<<(SElement const& se) {
        LinkedList<SElement*>::insertLast(se.clone());
        return *this;
    }

    SList(SElement const& x) {
        *this << x;
    }

    SList(SElement const& x,
          SElement const& y) {
        *this << x << y;
    }

    // извеждане
    void print(std::ostream& os) const {
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
    void collect(LinkedList<int>& l) const {
        for(SElement* se : *this)
            se->collect(l);
    }
};

#endif