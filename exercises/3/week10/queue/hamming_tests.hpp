#ifndef __HAMMING_TESTS_HPP
#define __HAMMING_TESTS_HPP

#include "hamming_generator.hpp"
#include "doctest.h"

// O(log k)
bool isHamming(unsigned k) {
    for(unsigned divisor : {2, 3, 5})
        while(k % divisor == 0)
            k /= divisor;
    return k == 1;
}

// време: O(n * log n)
// памет: O(1)
/*
    unsigned count = 0, i = 1;
    while (count <= n) {
        if (isHamming(i)) {
            std::cout << i << std::endl;
            count++;
            }
        i++;
    }
*/

// време: O(n)
// памет: O(n)
/*
    unsigned x;
    HammingGenerator hg;
    for(int i = 1; i <= n; i++) {
        hg >> x;
        std::cout << x << std::endl;
    }
*/


TEST_CASE("Първите 10 числа на Hamming се генерират успешно") {
    unsigned x;
    unsigned hamming[] = { 1, 2, 3, 4, 5, 6, 8, 9, 10, 12};
    HammingGenerator hg;
    for(int i = 0; i < 10; i++) {
        hg >> x;
        // std::clog << x << std::endl;
        CHECK_EQ(x, hamming[i]);
    }
}

TEST_CASE("1000 числа на Hamming в нарастващ ред се генерират успешно") {
    unsigned x, last = x;
    HammingGenerator hg;
    for(int i = 0; i < 1000; i++) {
        hg >> x;
        // std::clog << x << std::endl;
        CHECK(isHamming(x));
        CHECK(last < x);
        last = x;
    }
}


#endif