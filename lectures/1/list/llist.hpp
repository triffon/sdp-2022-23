#ifndef __LLIST_HPP
#define __LLIST_HPP

#include "abstract_list.hpp"
#include <cassert>
#include <stdexcept>

template <typename T>
struct LinkedListElement {
    T data;
    LinkedListElement* next;
    LinkedListElement(T const& _data, LinkedListElement* _next = nullptr)
        : data(_data), next(_next) {}
};

template <typename T>
class LinkedList;

template <typename T>
class LinkedListIterator : public Position<T, LinkedListIterator<T>> {
private:
    LinkedListElement<T>* ptr;
    friend class LinkedList<T>;
public:
    LinkedListIterator(LinkedListElement<T>* _ptr = nullptr) : ptr(_ptr) {}

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
    LinkedListIterator next() const {
        if (!valid())
            throw std::runtime_error("Опит за преместване на невалидна позиция!");
        return ptr->next;
    }

    // предишна позиция
    LinkedListIterator prev() const {
        throw std::logic_error("В едносвързания списък нямаме достъп до предишен елемент");
    }

    // сравнение на итератори
    bool operator==(Position<T, LinkedListIterator> const& pos) const {
        // !!! не се прави проверка дали pos е обект от LinkedListIterator
        // TODO: предложете решения!
        return ptr == ((LinkedListIterator const&)pos).ptr;
    }
};

template <typename T>
class LinkedList : public AbstractList<T, LinkedListIterator<T>>{
public:
    using I = LinkedListIterator<T>;
    using E = LinkedListElement<T>;
private:
    E *front, *back;

    // връща предишната позиция
    // или невалидна  позиция, ако предишна няма
    // O(n)
    I findPrev(I const& it) {
        I result = front;
        while (result.valid() && result.next() != it)
            ++result;
        // !result.valid() || result.next() == it
        return result;
    }
public:

    // TODO: голяма четворка
    LinkedList() : front(nullptr), back(nullptr) {}

    // включване на елемент преди дадена позиция
    // O(n)
    bool insertBefore(T const& x, I const& pos) {
        if (pos.ptr == front) {
            // специална реализация за вмъкване в началото
            front = new E{x, front};
            return true;
        }
        return insertAfter(x, findPrev(pos));
    }

    // включване на елемент след дадена позиция 
    // O(1)
    bool insertAfter(T const& x, I const& pos) {
        if (this->empty()) {
            // включване в празен списък
            front = back = new E(x);
            return true;
        }
        if (!pos.ptr) {
            // включваме последен елемент
            return insertAfter(x, I(back));
        }
        pos.ptr->next = new E(x, pos.ptr->next);
        if (pos.ptr == back)
            // трябва да обновим back, понеже вмъкваме след последния елемент
            back = back->next;
        return true;
    }

    // изключване на елемент преди дадена позиция 
    bool deleteBefore(T& x, I const& pos) {
        return false;
    }

    // изключване на елемент на дадена позиция, унищавайки позицията 
    bool deleteAt(T& x, I& pos) {
        if (!pos.valid())
            // опит за изтриване на невалиден елемент
            return false;
        I prev = findPrev(pos);
        if (!prev.valid()) {
            // опит за изтриване на първия елемент
            x = *pos;
            front = front->next;
            delete pos.ptr;
            return true;
        }
        if (pos.ptr == back)
            // опит за изтриване на последния елемент, трябва да преместим back
            back = prev.ptr;
        pos = I();
        return deleteAfter(x, prev);
    }

    // изключване на елемент след дадена позиция 
    // O(1)
    bool deleteAfter(T& x, I const& pos) {
        if (!pos.valid())
            return false;
        E* toDelete = pos.ptr->next;
        if (toDelete == nullptr)
            return false;
        pos.ptr->next = toDelete->next;
        x = toDelete->data;
        delete toDelete;
        return true;
    }

    I begin() const { return I(front); }
    I end()   const { return I(); }


};


#endif