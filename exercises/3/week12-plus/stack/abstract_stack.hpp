#ifndef __ABSTRACT_STACK
#define __ABSTRACT_STACK

template <typename T>
class AbstractStack {
public:
    // проверка за празнота
    virtual bool empty() const = 0;

    // включване на елемент
    virtual void push(T const& x) = 0;

    // намиране на последния включен елемент
    virtual T const& peek() const = 0;

    // изключване на последния включен елемент
    virtual T pop() = 0;

    // виртуален деструктор
    virtual ~AbstractStack() {}
};

#endif