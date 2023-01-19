#ifndef __DICTIONARY_TESTS_HPP
#define __DICTIONARY_TESTS_HPP

#include "doctest.h"
#include "list_dictionary.hpp"
#include "bst_dictionary.hpp"
#include "linked_hash.hpp"
#include <string>

unsigned lengthHashFunction(std::string const& str) {
    return str.length();
}

unsigned firstElementHashFunction(std::string const& str) {
    return str[0];
}

unsigned sumHashFunction(std::string const& str) {
    unsigned hash = 0;
    for (char c : str)
        hash += c;
    return hash;
}

unsigned betterHashFunction(std::string const& str) {
    unsigned hash = 0;
    unsigned i = 1;
    for (char c : str)
        hash += c * ((i += 5) *= 13);
    return hash;
}


using TestListDictionary = ListDictionary<std::string, unsigned>;
using TestBSTDictionary = BSTDictionary<std::string, unsigned>;
//using TestHashDictionary = LinkedHashTable<std::string, unsigned, lengthHashFunction, 10>;
//using TestHashDictionary = LinkedHashTable<std::string, unsigned, firstElementHashFunction, 100>;
//using TestHashDictionary = LinkedHashTable<std::string, unsigned, sumHashFunction, 100>;
using TestHashDictionary = LinkedHashTable<std::string, unsigned, betterHashFunction, 100>;

TYPE_TO_STRING(TestListDictionary);
TYPE_TO_STRING(TestBSTDictionary);
TYPE_TO_STRING(TestHashDictionary);

#define ALL_DICTIONARIES TestListDictionary, TestBSTDictionary, TestHashDictionary

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

    SUBCASE("Можем да намерим всички добавени елементи") {
        for(int x : { 12, 42, 135, 15, 7})
            CHECK_EQ(*dict.lookup(std::to_string(x)), x);
    }

    SUBCASE("Не можем да изтрием липсващ елемент") {
        CHECK(!dict.remove("missing"));
    }

    SUBCASE("Изтриваме успешно съществуващи елементи") {
//        dict.info();
        REQUIRE(dict.remove("135"));
//        dict.info();
        REQUIRE(dict.remove("15"));
//        dict.info();

        CHECK_EQ(dict.lookup("135"), nullptr);
        CHECK_EQ(dict.lookup("15"), nullptr);
        CHECK_EQ(*dict.lookup("12"), 12);
        CHECK_EQ(*dict.lookup("42"), 42);
        CHECK_EQ(*dict.lookup("7"), 7);
    }

    SUBCASE("Изброяваме коректно ключовете") {
        size_t len = 0;
        for(std::string key : dict.keys()) {
            CHECK((key == "135" || key == "15" || key == "42" || key == "7" || key == "12"));
            len++;
        }
        CHECK_EQ(len, 5);
    }

    SUBCASE("Изброяваме коректно стойностите") {
        size_t len = 0;
        for(unsigned value : dict.values()) {
            CHECK((value == 135 || value == 15 || value == 42 || value == 7 || value == 12));
            len++;
        }
        CHECK_EQ(len, 5);
    }

}

TEST_CASE_TEMPLATE("Добавяне и изтриване на 100 елемента",
    AnyDictionary, ALL_DICTIONARIES) {
    AnyDictionary dict;
    for(int i = 1; i <= 50; i++) {
        REQUIRE(dict.add(std::to_string(i), i));
        REQUIRE(dict.add(std::to_string(101 - i), 101 - i));
    }

    dict.info();

    for(int i = 1; i <= 100; i++)
        CHECK_EQ(*dict.lookup(std::to_string(i)), i);

    for(int i = 50; i > 10; i--) {
        CHECK(dict.remove(std::to_string(i)));
        CHECK(dict.remove(std::to_string(101 - i)));
    }

    dict.info();

    for(int i = 11; i <= 90; i++)
        CHECK_EQ(dict.lookup(std::to_string(i)), nullptr);

    for(int i = 1; i <= 10; i++) {
        CHECK_EQ(*dict.lookup(std::to_string(i)), i);
        CHECK_EQ(*dict.lookup(std::to_string(101 - i)), 101 - i);
    }
}

#endif