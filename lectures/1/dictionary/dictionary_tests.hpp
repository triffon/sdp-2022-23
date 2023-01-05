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

TEST_CASE_TEMPLATE("Добавяне и изтриване на елементи",
    AnyDictionary, ALL_DICTIONARIES) {

    AnyDictionary dict;
    for(int x : { 12, 42, 135, 15, 7})
        REQUIRE(dict.add(std::to_string(x), x));

    for(int x : { 12, 42, 135, 15, 7})
        CHECK_EQ(*dict.lookup(std::to_string(x)), x);

    CHECK(!dict.remove("missing"));

    REQUIRE(dict.remove("135"));
    REQUIRE(dict.remove("15"));

    CHECK_EQ(dict.lookup("135"), nullptr);
    CHECK_EQ(dict.lookup("15"), nullptr);
    CHECK_EQ(*dict.lookup("12"), 12);
    CHECK_EQ(*dict.lookup("42"), 42);
    CHECK_EQ(*dict.lookup("7"), 7);
}

#endif