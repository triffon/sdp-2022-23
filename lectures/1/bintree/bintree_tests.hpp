#ifndef __BINTREE_TEST_HPP
#define __BINTREE_TEST_HPP

#include "doctest.h"

#include <iostream>
#include <sstream>
#include "bintree.hpp"

using IntTree = BinTree<int>;

TEST_CASE("Извеждане на двоично дърво") {
    IntTree t(1, IntTree(2, IntTree(3), IntTree(4)),
                 IntTree(5, IntTree(), IntTree(6)));

    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2 (3 () ()) (4 () ())) (5 () (6 () ())))");
}

#endif