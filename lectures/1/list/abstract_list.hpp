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

    // преместваме се на предишната позиция
    // --it
    ConcretePosition& operator--() {
        return (ConcretePosition&)(*this) = prev();
    }

    // it--
    ConcretePosition operator--(int) {
        ConcretePosition save = (ConcretePosition&)*this;
        --*this;
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
        while (!empty()) {
            T x;
            deleteFirst(x);
        }
    }

public:
    // даваме възможност да подаваме списък където се очаква итератор
    // така се връща итератор към началото на списъка
    operator P() const { return begin(); }

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

    // merge с един параметър
    void merge(AbstractList const& l2) {
        P it2 = l2.begin();
        P it1 = this->begin();

        if(it1!=this->end()) {
            P previous;
            //не желая да използвам insertBefore, защото ще е бавно, затова ще го правя с previous
            while(*it1 > *it2 && it2!=l2.end()) { // случаите, в които трябва да вкараме елементите преди началото на l1
                if(!(previous.valid())) { // все още няма елемент преди началото на l1
                    insertFirst(*it2);
                    previous = begin();
                }
                else { //Вече сме вкарали един елемент преди l1, ползваме previous и InsertNext
                    insertAfter(*it2, previous);
                    previous++; //Изместване на елемента, който току що вкарахме
                }
                it2++;
            }
            //Сега просто ще гледам с един елемент напред.
            //И ще вкарвам между сегашния и следващия, ако следващият е по-голям.
            while(it2 != l2.end() && it1.next() != this->end()){
                if(*it1.next() > *it2)
                {
                    insertAfter(*it2, it1);
                    it2++;
                }
                it1++; //изместваме всеки път, независимо дали е вкаран елемент или не.
            }
        }
        //Ако има елементи, които не можем да вкараме вътре,
        //значи те вече са по-големи от всеки елемент в нашия списък и просто вкарваме останалите
        while(it2 != l2.end())
                insertLast(*it2++);
    }

    P find(T const& x) const {
        P pos = begin();
        while (pos && *pos != x)
            ++pos;
        return pos;
    }

    virtual ~AbstractList() {}
};

template <typename L /* extends AbstractList */>
class ListUtils {
public:
    static L mergeSort(L const& l) {
        if (l.empty() || !l.begin().next().valid())
            return l;
        L l1, l2;
        l.split(l1, l2);
        L result;
        result.merge(mergeSort(l1), mergeSort(l2));
        return result;
    }
};

#endif