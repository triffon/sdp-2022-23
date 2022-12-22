#ifndef __BINTREE_TEST_HPP
#define __BINTREE_TEST_HPP

#include "doctest.h"

#include <iostream>
#include <sstream>
#include "bintree.hpp"

using BIntTree = BinTree<int>;

TEST_CASE("Извеждане и дълбочина на двоично дърво") {
    BIntTree t(1, BIntTree(2, BIntTree(3), BIntTree(4)),
                 BIntTree(5, BIntTree(), BIntTree(6)));


    SUBCASE("Извеждане") {
        std::ostringstream os;
        t.print(os);
        CHECK_EQ(os.str(), "(1 (2 (3 () ()) (4 () ())) (5 () (6 () ())))");
    }

    SUBCASE("Дълбочина") {
        CHECK_EQ(t.depth(), 3);
    }

    SUBCASE("Копиране") {
        BIntTree* t2 = new BIntTree(t);
        *(t2->root()) = 10;
        delete t2;
        CHECK_EQ(*t.root(), 1);
    }

    SUBCASE("Присвояване") {
        BIntTree* t2 = new BIntTree;
        *t2 = t;
        *(t2->root()) = 10;
        delete t2;
        CHECK_EQ(*t.root(), 1);
    }
}

#endif