#ifndef __SLIST_HPP
#define __SLIST_HPP

#include "selement.hpp"

class SList : public LinkedList<SElement*>,
              public SElement {
private:
    void cloneAll() {
        for(SElement* se : *this)
            se = se->clone();
    }

    void deleteAll() {
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
        std::clog << "След клонирането: ";
        print(std::clog);
        std::clog << std::endl;
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
        std::clog << "Унищожаваме списък: ";
        print(std::clog);
        std::clog << std::endl;
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