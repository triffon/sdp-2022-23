#ifndef __DICTIONARY_TESTS_HPP
#define __DICTIONARY_TESTS_HPP

#include "doctest.h"
#include "list_dictionary.hpp"
#include "bst_dictionary.hpp"
#include <string>

TYPE_TO_STRING(ListDictionary<std::string, unsigned>);
TYPE_TO_STRING(BSTDictionary<std::string, unsigned>);

#define ALL_DICTIONARIES ListDictionary<std::string, unsigned>, BSTDictionary<std::string, unsigned>

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
        REQUIRE(dict.remove("135"));
        REQUIRE(dict.remove("15"));

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

    for(int i = 1; i <= 100; i++)
        CHECK_EQ(*dict.lookup(std::to_string(i)), i);

    for(int i = 50; i > 10; i--) {
        CHECK(dict.remove(std::to_string(i)));
        CHECK(dict.remove(std::to_string(101 - i)));
    }

    for(int i = 11; i <= 90; i++)
        CHECK_EQ(dict.lookup(std::to_string(i)), nullptr);

    for(int i = 1; i <= 10; i++) {
        CHECK_EQ(*dict.lookup(std::to_string(i)), i);
        CHECK_EQ(*dict.lookup(std::to_string(101 - i)), 101 - i);
    }
}

#endif