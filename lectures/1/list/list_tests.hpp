#include "doctest.h"
#include "llist.hpp"
#include <cmath>

TYPE_TO_STRING(LinkedList<int>);
#define ALL_LISTS LinkedList<int>

TEST_CASE_TEMPLATE("При създаване на списък той е празен",
                    AnyList, ALL_LISTS) {
    AnyList l;
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("При добавяне на елемент в списък той вече не е празен",
                    AnyList, ALL_LISTS) {
    AnyList l;
    REQUIRE(l.insertLast(42));
    CHECK(!l.empty());
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка и обхождането му",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Последователно добавяне на елементи в списъка от началото и обхождането му",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertFirst(i));

    int i = 10;
    for(int x : l)
        CHECK_EQ(i--, x);
    CHECK_EQ(i, 0);
}

TEST_CASE_TEMPLATE("Включване на елементи на четни позиции",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i += 2)
        REQUIRE(l.insertLast(i));

    // TODO: it += 2;
    for(typename AnyList::I it = l.begin(); it != l.end(); ++it, ++it)
        REQUIRE(l.insertAfter(*it + 1, it));

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Включване на елементи на нечетни позиции с insertBefore",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 2; i <= 10; i += 2)
        REQUIRE(l.insertLast(i));

    // TODO: it += 2;
    for(typename AnyList::I it = l.begin(); it != l.end(); ++it)
        l.insertBefore(*it - 1, it);

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Изключване на елементи на четни позиции с deleteAfter",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i ++)
        REQUIRE(l.insertLast(i));

    int x;
    int i = 2;

    for(typename AnyList::I it = l.begin(); it != l.end(); i += 2, ++it) {
        REQUIRE(l.deleteAfter(x, it));
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 12);

    // трябва все още да можем да вмъкнем в края на списъка
    REQUIRE(l.insertLast(11));

    i = -1;
    for(int x : l)
        CHECK_EQ(i += 2, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Последователно изтриване на последния елемент в списъка",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    int x;
    for(int i = 10; i >= 1; i--) {
        REQUIRE(l.deleteLast(x));
        CHECK_EQ(x, i);
    }
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("Последователно изтриване на първия елемент в списъка",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    int x;
    for(int i = 1; i <= 10; i++) {
        REQUIRE(l.deleteFirst(x));
        CHECK_EQ(x, i);
    }
    CHECK(l.empty());
}

TEST_CASE_TEMPLATE("Изключване на елементи на четни позиции с deleteAt",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i ++)
        REQUIRE(l.insertLast(i));

    int x;
    int i = 2;

    for(typename AnyList::I it = l.begin().next(); it != l.end(); i += 2, it && ++it) {
        typename AnyList::I toDelete = it++;
        REQUIRE(l.deleteAt(x, toDelete));
        CHECK(!toDelete.valid());
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 12);

    i = -1;
    for(int x : l)
        CHECK_EQ(i += 2, x);
    CHECK_EQ(i, 9);
}

TEST_CASE_TEMPLATE("Изключване на елементи на нечетни позиции с deleteBefore",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));

    int i = 1;
    int x;
    for(typename AnyList::I it = l.begin().next(); it != l.end(); i += 2,  ++it && ++it) {
        REQUIRE(l.deleteBefore(x, it));
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 11);

    i = 0;
    for(int x : l)
        CHECK_EQ(i += 2, x);
    CHECK_EQ(i, 10);
}

TEST_CASE_TEMPLATE("Конкатениране на два списъка с append",
                    AnyList, ALL_LISTS) {
    AnyList l1, l2;
    int i = 1;
    for(; i <= 10; i++)
        l1.insertLast(i);
    for(; i <= 20; i++)
        l2.insertLast(i);
    l1.append(l2);
    i = 1;
    for(int x : l1)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 21);
}

TEST_CASE_TEMPLATE("Конкатениране на два списъка с appendAndDestroy",
                    AnyList, ALL_LISTS) {
    AnyList l1, l2;
    int i = 1;
    for(; i <= 10; i++)
        l1.insertLast(i);
    for(; i <= 20; i++)
        l2.insertLast(i);
    l1.appendAssign(l2);
    CHECK(l2.empty());
    i = 1;
    for(int x : l1)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 21);
}

TEST_CASE_TEMPLATE("Конструкторът за копиране не споделя памет",
                    AnyList, ALL_LISTS) {
    AnyList l1;
    for(int i = 1; i <= 10; i++)
        l1.insertLast(i);
    AnyList l2 = l1;
    l2.insertLast(20);
    for(int i = 1; i <= 10; i++) {
        CHECK(! l1.empty());
        int x;
        REQUIRE(l1.deleteFirst(x));
        CHECK_EQ(x, i);
    }
    CHECK(l1.empty());
}

TEST_CASE_TEMPLATE("Обръщане на списък от един елемент",
                    AnyList, ALL_LISTS) {
    AnyList l;
    l.insertLast(42);
    l.reverse();
    for(int x : l)
        CHECK_EQ(x, 42);
}

TEST_CASE_TEMPLATE("Обръщане на списък",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int i = 1; i <= 10; i++)
        REQUIRE(l.insertLast(i));
    l.reverse();
    int i = 10;
    for(int x : l)
        CHECK_EQ(x, i--);
    CHECK_EQ(i, 0);
}


TEST_CASE("Обръщане на списък чрез препратки") {
    LinkedList<int> l;
    int i = 1;
    for(i ; i <= 10; i++)
        l.insertLast(i);

    l.reverseAssign();
    CHECK_EQ(10, l.begin().get());

    for(int x : l)
        CHECK_EQ(x, i--);
    CHECK_EQ(i, 0);

    l.reverseAssign();

    i=1;
    for(int x : l)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Разделяне на списък с четен брой елементи на две равни части",
                    AnyList, ALL_LISTS) {
    const size_t N = 10;
    AnyList l, l1, l2;
    for(int i = 0; i < N; i++)
        l.insertLast(i);
    l.split(l1, l2);

    bool used[N] = { false };
    size_t n1 = 0, n2 = 0;
    for(int x : l1) {
        n1++;
        CHECK(!used[x]);
        used[x] = true;
    }

    for(int x : l2) {
        n2++;
        CHECK(!used[x]);
        used[x] = true;
    }

    CHECK(n1 == n2);
    int i = 0;
    while (i < N && used[i++]);
    CHECK(i == N);
}

TEST_CASE_TEMPLATE("Разделяне на списък с нечетен брой елементи на две равни части",
                    AnyList, ALL_LISTS) {
    const size_t N = 11;
    AnyList l, l1, l2;
    for(int i = 0; i < N; i++)
        l.insertLast(i);
    l.split(l1, l2);

    bool used[N] = { false };
    size_t n1 = 0, n2 = 0;
    for(int x : l1) {
        n1++;
        CHECK(!used[x]);
        used[x] = true;
    }

    for(int x : l2) {
        n2++;
        CHECK(!used[x]);
        used[x] = true;
    }

    CHECK(abs(n1 - n2) == 1);
    int i = 0;
    while (i < N && used[i++]);
    CHECK(i == N);
}

TEST_CASE_TEMPLATE("Разделяне на списък с нечетен брой елементи на две равни части",
                    AnyList, ALL_LISTS) {
    AnyList l, l1, l2;
    for(int x : {1, 2, 3, 5, 8})
        l1.insertLast(x);
    for(int x : {4, 6, 7, 9, 10})
        l2.insertLast(x);

    l.merge(l1, l2);

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Сортиране на списък чрез сливане",
                    AnyList, ALL_LISTS) {
    AnyList l;
    for(int x : {1, 5, 7, 2, 6, 4, 9, 10, 8, 3})
        l.insertLast(x);

    l = ListUtils<AnyList>::mergeSort(l);

    int i = 1;
    for(int x : l)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 11);
}