#ifndef __DLLIST_HPP
#define __DLLIST_HPP

#include "abstract_list.hpp"
#include <cassert>
#include <stdexcept>

template <typename T>
struct DoubleLinkedListElement {
    T data;
    DoubleLinkedListElement *prev, *next;
    DoubleLinkedListElement(T const& _data,
                            DoubleLinkedListElement* _next = nullptr,
                            DoubleLinkedListElement* _prev = nullptr)
        : data(_data), next(_next), prev(_prev) {}
};

template <typename T>
class DoubleLinkedList;

template <typename T>
class DoubleLinkedListIterator : public Position<T, DoubleLinkedListIterator<T>> {
private:
    DoubleLinkedListElement<T>* ptr;
    friend class DoubleLinkedList<T>;
public:
    DoubleLinkedListIterator(DoubleLinkedListElement<T>* _ptr = nullptr) : ptr(_ptr) {}

    // проверка за валидност на позицията
    bool valid() const { return ptr != nullptr; }

    // константен достъп до елемента на позицията
    T const& get() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп през невалидна позиция!");
        return ptr->data;
    }

    // достъп до елемента на позицията с възможност за промяна
    T& get() {
        if (!valid())
            throw std::runtime_error("Опит за достъп през невалидна позиция!");
        return ptr->data;
    }

    // следваща позиция
    DoubleLinkedListIterator next() const {
        if (!valid())
            throw std::runtime_error("Опит за преместване на невалидна позиция!");
        return ptr->next;
    }

    // предишна позиция
    DoubleLinkedListIterator prev() const {
        if (!valid())
            throw std::runtime_error("Опит за преместване на невалидна позиция!");
        return ptr->prev;
    }

    // сравнение на итератори
    bool operator==(Position<T, DoubleLinkedListIterator> const& pos) const {
        // !!! не се прави проверка дали pos е обект от DoubleLinkedListIterator
        // TODO: предложете решения!
        return ptr == ((DoubleLinkedListIterator const&)pos).ptr;
    }
};

template <typename T>
class DoubleLinkedList : public AbstractList<T, DoubleLinkedListIterator<T>>{
public:
    using I = DoubleLinkedListIterator<T>;
    using E = DoubleLinkedListElement<T>;
private:
    E *front, *back;

public:

    // голяма четворка
    DoubleLinkedList() : front(nullptr), back(nullptr) {}

    DoubleLinkedList(DoubleLinkedList const& other) : front(nullptr), back(nullptr) {
        this->append(other);
    }

    DoubleLinkedList& operator=(DoubleLinkedList const& other) {
        if (this != &other) {
            this->erase();
            this->append(other);
        }
        return *this;
    }

    ~DoubleLinkedList() {
        this->erase();
    }

    // включване на елемент преди дадена позиция
    // O(n)
    bool insertBefore(T const& x, I const& pos) {
        return false;
    }

    // включване на елемент след дадена позиция 
    // O(1)
    bool insertAfter(T const& x, I const& pos) {
        return false;
    }

    // изключване на елемент преди дадена позиция 
    bool deleteBefore(T& x, I const& pos) {
        return false;
    }

    // изключване на елемент на дадена позиция, унищавайки позицията
    bool deleteAt(T& x, I& pos) {
        return false;
    }

    // изключване на елемент след дадена позиция 
    bool deleteAfter(T& x, I const& pos) {
        return false;
    }

    I begin() const { return I(front); }
    I last()  const { return I(back); }
    I end()   const { return I(); }

    void appendAssign(DoubleLinkedList& other) {
    }

    // TODO: reverseAssign
    // TODO: splitAssign
    // TODO: mergeAssign
};

#endif