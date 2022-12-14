#ifndef __HAMMING_GENERATOR
#define __HAMMING_GENERATOR
#include <iostream>
#include <streambuf>
#include <charconv>

#include "lqueue.hpp"

class HammingGeneratorBuffer : public std::streambuf {
private:
    using LQ = LinkedQueue<unsigned>;
    LQ q2, q3, q5;
    static const size_t SIZE = 10;
    char buffer[SIZE];
protected:
    int_type underflow() {
        unsigned m = std::min(q2.head(), std::min(q3.head(), q5.head()));
        LQ* qs[] = {&q2, &q3, &q5};
        for(LQ* q : qs)
            if (q->head() == m)
                q->dequeue();
        q2.enqueue(2 * m);
        q3.enqueue(3 * m);
        q5.enqueue(5 * m);
        // !!! return m;
        // сега трябва да запишем символното представяне на m в буфера
        char* last = std::to_chars(buffer, buffer + SIZE, m).ptr;
        *last++ = '\n';
        setg(buffer, buffer, last);
        return buffer[0];
    }
public:
    HammingGeneratorBuffer() {
        q2.enqueue(1);
        q3.enqueue(1);
        q5.enqueue(1);
    }
};

class HammingGenerator : public std::istream {
private:
    HammingGeneratorBuffer hgbuf;
public:
    HammingGenerator() : std::istream(&hgbuf) {}
};


#endif