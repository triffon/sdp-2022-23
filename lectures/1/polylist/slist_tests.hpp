#ifndef __SLIST_TESTS_HPP
#define __SLIST_TESTS_HPP

#include "doctest.h"
#include <sstream>
#include "sint.hpp"
#include "slist.hpp"

TEST_CASE("Извеждане и събиране на елементи от дълбок списък") {
    SList()
            <<  SList()
            <<  SList(SInt(7));

    SList sl = SList()
    << 
        SList(SInt(1), SList(SInt(2)))
    <<
        (SList()
            <<  SList(SList(SInt(3)), SInt(4))
            <<  SList(SInt(5), SList(SInt(6)))
            <<  SList()
            <<  SList(SInt(7)))
    << SInt(8);

    std::ostringstream os;
    sl.print(os);
    CHECK_EQ(os.str(), "((1 (2)) (((3) 4) (5 (6)) () (7)) 8)");

    LinkedList<int> result;
    sl.collect(result);

    int i = 1;
    for(int x : result)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 9);
}

#endif