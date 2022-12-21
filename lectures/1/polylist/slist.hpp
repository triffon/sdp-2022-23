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
    SList* steal() { return new SList(std::move(*this)); }

    SList() {}

    SList(SList const& other) : LinkedList<SElement*>(other) {
        std::clog << "Клонираме списък: ";
        print(std::clog);
        std::clog << std::endl;
        cloneAll();
    }

    SList(SList&& other) : LinkedList<SElement*>(std::move(other)) {
        std::clog << "Преместваме списък: ";
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
        deleteAll();
    }

    SList& operator<<(SElement const& se) {
        std::clog << "Добавяме с копиране: ";
        se.print(std::clog);
        std::clog << std::endl;
        LinkedList<SElement*>::insertLast(se.clone());
        return *this;
    }

    SList&& operator<<(SElement&& se) {
        std::clog << "Добавяме с преместване: ";
        se.print(std::clog);
        std::clog << std::endl;
        LinkedList<SElement*>::insertLast(se.steal());
        return std::move(*this);
    }

    // конструктор за списък с копиране на един елемент
    SList(SElement const& x) {
        *this << x;
    }

    // конструктор за списък с копиране на два елемента
    SList(SElement const& x,
          SElement const& y) {
        *this << x << y;
    }

    // конструктор за списък с преместване на един елемент
    SList(SElement&& x) {
        *this << std::move(x);
    }

    // конструктор за списък с преместване на два елемента
    SList(SElement&& x, SElement&& y) {
        *this << std::move(x) << std::move(y);
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