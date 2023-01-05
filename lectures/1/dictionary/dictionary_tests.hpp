#ifndef __DICTIONARY_TESTS_HPP
#define __DICTIONARY_TESTS_HPP

#include "doctest.h"
#include "list_dictionary.hpp"

#define ALL_DICTIONARIES ListDictionary<std::string, unsigned>

TEST_CASE_TEMPLATE("Добавяне на елемент в празен речник",
    AnyDictionary, ALL_DICTIONARIES) {
    AnyDictionary dict;
    CHECK_EQ(dict.lookup("the_answer"), nullptr);
    REQUIRE(dict.add("the_answer", 42));
    CHECK_EQ(*dict.lookup("the_answer"), 42);
    CHECK(!dict.add("the_answer", 43));
}

#endif