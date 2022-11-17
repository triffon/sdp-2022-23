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
public:
    virtual bool empty() const { return !begin().valid(); }

    // включване на първи елемент
    virtual bool insertFirst(T const& x) { return insertBefore(x, begin()); }

    // включване на последен елемент
    virtual bool insertLast(T const& x) { return insertAfter(x, end()); }

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

    virtual ~AbstractList() {}
};

#endif