#ifndef __ABSTRACT_LIST_HPP
#define __ABSTRACT_LIST_HPP

#include <stdexcept>

template <typename T, typename ConcretePosition /* extends Position<T> */>
class Position {
public:
    // проверка за валидност на позицията
    virtual bool valid() const = 0;

    // if (it) ...
    // if (!it) ...

    operator bool() const { return valid(); }
    bool operator!() const { return !valid(); } 

    // константен достъп до елемента на позицията
    virtual T const& get() const = 0;

    // достъп до елемента на позицията с възможност за промяна
    virtual T& get() = 0;

    // следваща позиция
    virtual ConcretePosition next() const = 0;

    // предишна позиция
    virtual ConcretePosition prev() const = 0;

    // преместваме се на следващата позиция
    // ++it
    ConcretePosition& operator++() {
        return (ConcretePosition&)(*this) = next();
    }

    // it++
    ConcretePosition operator++(int) {
        ConcretePosition save = (ConcretePosition&)*this;
        ++*this;
        return save;
    }

    // операции за сравнение
    virtual bool operator==(Position const& pos) const = 0;
    bool operator!=(Position const& pos) { return !(*this == pos); }

    T const& operator*() const { return get(); } 
    T&       operator*()       { return get(); } 
};

template <typename T, typename P /* extends Position<T> */>
class AbstractList {
protected:
    void erase() {
        T x;
        while (!empty())
            deleteFirst(x);
    }

public:
    virtual bool empty() const { return !begin().valid(); }

    // включване на първи елемент
    virtual bool insertFirst(T const& x) { return insertBefore(x, begin()); }

    // включване на последен елемент
    virtual bool insertLast(T const& x) { return insertAfter(x, last()); }

    // включване на елемент преди дадена позиция 
    virtual bool insertBefore(T const& x, P const& pos) = 0;

    // включване на елемент след дадена позиция 
    virtual bool insertAfter(T const& x, P const& pos) = 0;  

    // изключване на първи елемент
    virtual bool deleteFirst(T& x) {
        P pos = begin();
        return deleteAt(x, pos);
    }

    // изключване на последен елемент
    virtual bool deleteLast(T& x) {
        P pos = last();
        return deleteAt(x, pos);
    }

    // изключване на елемент преди дадена позиция 
    virtual bool deleteBefore(T& x, P const& pos) = 0;  

    // изключване на елемент на дадена позиция, унищавайки позицията 
    virtual bool deleteAt(T& x, P& pos) = 0;  

    // изключване на елемент след дадена позиция 
    virtual bool deleteAfter(T& x, P const& pos) = 0;  

    // константен достъп до елемент на дадена позиция
    virtual T const& getAt(P const& pos) const {
        if (!pos.valid())
            throw std::runtime_error("Опит за достъп през невалидна позиция!");
        return pos.get();
    }

    // достъп до елемент на дадена позиция с възможност за промяна
    virtual T& getAt(P& pos) {
        if (!pos.valid())
            throw std::runtime_error("Опит за достъп през невалидна позиция!");
        return pos.get();
    }

    // !!! пробив във класа, можем да променяме елементите на константен
    // списък
    // TODO: да се реализира ConstPosition

    // връща позицията в началото
    virtual P begin() const = 0;

    // връща позицията в края
    virtual P last() const = 0;

    // връща позцията СЛЕД края
    // [begin; end)
    virtual P end() const = 0;

    // конкатениране на списък на края на дадения
    // O(|other|)
    void append(AbstractList const& other) {
        for(T const& x : other)
            insertLast(x);
    }

    void reverse() {
        T x;
        /*
        P originalFront = begin();
        // O(n²)
        while (originalFront != last()) {
            // O(n)
            deleteLast(x);
            // O(n)
            insertBefore(x, originalFront);
        }
        */
        P originalBack = last();
        // O(n) по памет и по време
        while (originalBack != begin()) {
            // O(1)
            deleteFirst(x);
            // O(1)
            insertAfter(x, originalBack);
        }
    }

    // разделя списъка на приблизително равни части
    // O(n) по време и по памет
    void split(AbstractList& l1, AbstractList& l2) const {
        AbstractList *me = &l1, *you = &l2;
        for(T x : *this) {
            you->insertLast(x);
            std::swap(me, you);
        }
    }

    // слива два списъка в текущия
    void merge(AbstractList const& l1, AbstractList const& l2) {
        P it1 = l1.begin(), it2 = l2.begin();
        while(it1 != l1.end() && it2 != l2.end())
            if (*it1 < *it2)
                insertLast(*it1++);
            else
                insertLast(*it2++);
        // прехвърляме от първия списък каквото е останало
        while(it1 != l1.end())
            insertLast(*it1++);
        while(it2 != l2.end())
            insertLast(*it2++);
    }

    // TODO: merge с един параметър
    // l1.merge(l2)

    void mergeSort() {
        
    }

    virtual ~AbstractList() {}
};

#endif