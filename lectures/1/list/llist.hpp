#ifndef __LLIST_HPP
#define __LLIST_HPP

#include "abstract_list.hpp"
#include <stdexcept>

// LinkedList<T>::LinkedListElement

template <typename T>
class LinkedList {
private:
    struct Element {
        T data;
        Element* next;
        Element(T const& _data, Element* _next = nullptr)
            : data(_data), next(_next) {}
    };

public:
    class Iterator : public Position<T, Iterator> {
    private:
        Element* ptr;
    public:
        // проверка за валидност на позицията
        bool valid() const { return ptr != nullptr; }

        // константен достъп до елемента на позицията
        T const& get() const {
            assert(valid());
            return ptr->data;
        }

        // достъп до елемента на позицията с възможност за промяна
        T& get() {
            assert(valid());
            return ptr->data;
        }

        // следваща позиция
        Iterator next() const {
            assert(valid());
            return ptr->next;
        }

        // предишна позиция
        Iterator prev() const {
            throw std::logic_error("В едносвързания списък нямаме достъп до предишен елемент");
        }
    };
};

#endif