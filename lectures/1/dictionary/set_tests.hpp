#ifndef __SET_TESTS_HPP
#define __SET_TESTS_HPP

#include "doctest.h"
#include "linked_hash.hpp"
#include "set.hpp"

template <typename K, typename V>
using SimpleLinkedHashTable = LinkedHashTable<K, V, trivialHashFunction, 100>;

using TestSet = Set<int, SimpleLinkedHashTable>;

#define ALL_SETS TestSet

TEST_CASE_TEMPLATE("Прост тест за множества", AnySet, ALL_SETS) {
    AnySet set;
    REQUIRE(set.empty());

    REQUIRE(set.insert(15));
    REQUIRE(set.insert(42));
    REQUIRE(set.insert(135));

    for (int x : {15, 42, 135})
        CHECK(set.contains(x));
    
    REQUIRE(!set.remove(100));
    REQUIRE(set.remove(42));
    REQUIRE(!set.contains(42));
}

#endif