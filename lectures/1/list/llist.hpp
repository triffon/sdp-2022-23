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

    LinkedList(LinkedList const& other) : front(nullptr), back(nullptr) {
        this->append(other);
    }

    LinkedList& operator=(LinkedList const& other) {
        if (this != &other) {
            this->erase();
            this->append(other);
        }
        return *this;
    }

    ~LinkedList() {
        this->erase();
    }

    // включване на елемент преди дадена позиция
    // O(n)
    bool insertBefore(T const& x, I const& pos) {
        if (this->empty())
            // искаме позицията да е невалидна понеже списъкът е празен
            assert(!pos.valid());

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
        pos.ptr->next = new E(x, pos.ptr->next);
        if (pos.ptr == back)
            // трябва да обновим back, понеже вмъкваме след последния елемент
            back = back->next;
        return true;
    }

    // изключване на елемент преди дадена позиция 
    bool deleteBefore(T& x, I const& pos) {
        if (this->empty())
            return false;
        if (pos.ptr == front)
            // опит за изтриване преди първия елемент
            return false;
        I prev = findPrev(pos);
        return deleteAt(x, prev);
    }

    // изключване на елемент на дадена позиция, унищавайки позицията
    // O(n)
    bool deleteAt(T& x, I& pos) {
        if (this->empty())
            return false;
        if (!pos.valid())
            // опит за изтриване на невалидна позиция
            return false;
        I prev = findPrev(pos);
        if (!prev.valid()) {
            // опит за изтриване на първия елемент
            x = *pos;
            front = front->next;
            back = nullptr;
            delete pos.ptr;
            return true;
        }
        pos = I();
        return deleteAfter(x, prev);
    }

    // изключване на елемент след дадена позиция 
    // O(1)
    bool deleteAfter(T& x, I const& pos) {
        if (this->empty())
            return false;
        if (!pos.valid())
            return false;
        E* toDelete = pos.ptr->next;
        if (toDelete == nullptr)
            // опит за изключване след последния елемент
            return false;
        if (toDelete == back)
            // изтриваме последния елемент, трябва да пренасочим back
            back = pos.ptr;
        pos.ptr->next = toDelete->next;
        x = toDelete->data;
        delete toDelete;
        return true;
    }

    I begin() const { return I(front); }
    I last()  const { return I(back); }
    I end()   const { return I(); }

    //O(n) по време, O(1) по памет
    unsigned long long getLength() const{
        I current = this->begin();
        unsigned long long length = 0;
        while(current!=this->end()){
            current++;
            length++;
        }
        return length;
    }

    void appendAssign(LinkedList& other) {
        back->next = other.front;
        back = other.back;
        other.back = other.front = nullptr;
    }

    // TODO: reverseAssign

    // O(n) по време
    // splitAssign
    void splitAssign(LinkedList& other){

        unsigned long long length = this->getLength();
        unsigned long long index_to_split = length/2 + length%2; //гледаме къде трябва да разделим списъка.
        if(length==0)
            return; // няма какво да се прави

        E* new_front = front;
        E* previous = nullptr;

        while(index_to_split!=0){
            if(index_to_split==1)
                previous = new_front; //взимаме предишния елемент преди да итерираме
            new_front = new_front->next;
            index_to_split--;
        }

        other.front = new_front;
        other.back = this->back;


        this->back = previous;      //слагаме новия край на първия списък
        this->back->next =nullptr;
    }

    // TODO: mergeAssign
};


#endif