#ifndef __ABSTRACT_LIST_HPP
#define __ABSTRACT_LIST_HPP

#include <stdexcept>

template <typename T, typename ConcretePosition /* extends Position<T> */>
class Position {
public:
    // проверка за валидност на позицията
    virtual bool valid() const = 0;

    // константен достъп до елемента на позицията
    virtual T const& get() const = 0;

    // достъп до елемента на позицията с възможност за промяна
    virtual T& get() = 0;

    // следваща позиция
    virtual ConcretePosition next() const = 0;

    // предишна позиция
    virtual ConcretePosition prev() const = 0;
};

template <typename T, typename P /* extends Position<T> */>
class AbstractList {
public:
    virtual bool empty() const = 0;

    // включване на първи елемент
    virtual void insertFirst(T const& x) = 0;  

    // включване на последен елемент
    virtual void insertLast(T const& x) = 0; 

    // включване на елемент преди дадена позиция 
    virtual bool insertBefore(T const& x, P const& pos) = 0;  

    // включване на елемент след дадена позиция 
    virtual bool insertAfter(T const& x, P const& pos) = 0;  

    // изключване на първи елемент
    virtual bool deleteFirst(T& x) = 0;  

    // изключване на последен елемент
    virtual bool deleteLast(T& x) = 0; 

    // изключване на елемент преди дадена позиция 
    virtual bool deleteBefore(T& x, P const& pos) = 0;  

    // изключване на елемент на дадена позиция, унищавайки позицията 
    virtual bool deleteAt(T& x, P& pos) = 0;  

    // изключване на елемент след дадена позиция 
    virtual bool deleteAfter(T& x, P const& pos) = 0;  

    // константен достъп до елемент на дадена позиция
    virtual T const& getAt(P const& pos) const {
        if (!valid(pos))
            throw std::runtime_error("Опит за достъп през невалидна позиция!");
        return pos.get();
    }

    // достъп до елемент на дадена позиция с възможност за промяна
    virtual T& getAt(P& pos) {
        if (!valid(pos))
            throw std::runtime_error("Опит за достъп през невалидна позиция!");
        return pos.get();
    }

    // !!! пробив във класа, можем да променяме елементите на константен
    // списък
    // TODO: да се реализира ConstPosition
    virtual P begin() const = 0;
    virtual P end() const = 0;

    virtual ~AbstractList() {}
};

#endif