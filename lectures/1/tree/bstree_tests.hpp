#ifndef __BSTREE_TESTS_HPP
#define __BSTREE_TESTS_HPP

#include "doctest.h"
#include "bstree.hpp"

using BSIntTree = BinSearchTree<int>;

TEST_CASE("Включване и търсене на елементи") {
    BSIntTree bst;

    REQUIRE(bst.insert(5));
    REQUIRE(bst.insert(3));
    REQUIRE(bst.insert(7));
    REQUIRE(bst.insert(6));
    REQUIRE(bst.insert(2));

    // bst.print(std::clog);

    // не можем да включваме същия елемент повторно
    REQUIRE(!bst.insert(3));

    for(int x : {2, 3, 5, 6, 7})
        CHECK_EQ(*bst.search(x), x);
    
    CHECK(!bst.search(1));
}

#endif