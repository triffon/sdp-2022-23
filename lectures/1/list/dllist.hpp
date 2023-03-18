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

    void insertInEmptyList(T const& x) {
        front = back = new E(x);
    }
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
    // O(1)
    bool insertBefore(T const& x, I const& pos) {
        if (this->empty()) {
            insertInEmptyList(x);
            return true;
        }
        // включване на невалидна позиция в непразен списък
        if (!pos.valid())
            return false;
        // включване преди първия елемент
        if (!pos.prev().valid()) {
            pos.ptr->prev = front = new E(x, pos.ptr, nullptr);
            return true;
        }
        // общ случай
        return insertAfter(x, pos.prev());
    }

    // включване на елемент след дадена позиция
    // O(1)
    bool insertAfter(T const& x, I const& pos) {
        // включване на елемент в празен списък
        if (this->empty()) {
            insertInEmptyList(x);
            return true;
        }
        // включване на невалидна позиция в непразен списък
        if (!pos.valid())
            return false;
        // включване след последния елемент
        if (!pos.next().valid()) {
            pos.ptr->next = back = new E(x, nullptr, pos.ptr);
            return true;
        }
        // общ случай
        pos.ptr->next = pos.ptr->next->prev = new E(x, pos.ptr->next, pos.ptr);
        return true;
    }

    // изключване на елемент преди дадена позиция
    bool deleteBefore(T& x, I const& pos) {
        // опит за изключване от невалидна позиция
        if (!pos.valid())
            return false;
        I prev = pos.prev();
        // общ случай
        return deleteAt(x, prev);
    }

    // изключване на елемент на дадена позиция, унищавайки позицията
    bool deleteAt(T& x, I& pos) {
        // опит за изключване от празен списък или невалидна позиция
        if (this->empty() || !pos.valid())
            return false;
        // общ случай
        (pos.ptr->prev ? pos.ptr->prev->next : front) = pos.ptr->next;
        (pos.ptr->next ? pos.ptr->next->prev : back)  = pos.ptr->prev;
        /*
        if (pos.ptr->next != nullptr)
            pos.ptr->next->prev = pos.ptr->prev;
        else
            back = pos.ptr->prev;
        */
        x = pos.ptr->data;
        delete pos.ptr;
        // трябва да инвалидираме позицията
        pos.ptr = nullptr;
        return true;
    }

    // изключване на елемент след дадена позиция
    bool deleteAfter(T& x, I const& pos) {
        // опит за изключване от невалидна позиция
        if (!pos.valid())
            return false;
        I next = pos.next();
        // общ случай
        return deleteAt(x, next);
    }

    I begin() const { return I(front); }
    I last()  const { return I(back); }
    I end()   const { return I(); }

    void appendAssign(DoubleLinkedList& other) {
        back->next = other.front;
        other.front->prev = back;
        back = other.back;
        other.back = other.front = nullptr;
    }

    // reverseAssign
    void reverseAssign(){
        E* current = front;
        E* previous = nullptr;              //взимаме два елемента, които са и нужни

        while(current)                      // итерираме, докато не е nullptr
        {
            previous = current->prev;       // взимаме предишния.
            current->prev = current->next;  // местим указателя за предишния елемент напред.
            current->next = previous;       // местим указателя за следващия елемент назад.
            current = current->prev;        // местим сегашния елемент към 'следващия', който сега е предишен.
        }

        std::swap(front, back);              //връщаме си back и front на местата им.
    }
    // TODO: splitAssign
    // TODO: mergeAssign

    bool isPalindrome() const {
        I fi = begin(), bi = last();
        while(fi != bi && fi.next() != bi && *fi == *bi) {
            ++fi;
            --bi;
        }
        return *fi == *bi;
    }
};

#endif