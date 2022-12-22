#ifndef __BINTREE_TEST_HPP
#define __BINTREE_TEST_HPP

#include "doctest.h"

#include <iostream>
#include <sstream>
#include "bintree.hpp"

using BIntTree = BinTree<int>;

TEST_CASE("Извеждане на двоично дърво") {
    BIntTree t(1, BIntTree(2, BIntTree(3), BIntTree(4)),
                 BIntTree(5, BIntTree(), BIntTree(6)));

    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2 (3 () ()) (4 () ())) (5 () (6 () ())))");
}

#endif