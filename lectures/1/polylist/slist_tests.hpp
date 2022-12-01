#ifndef __SLIST_TESTS_HPP
#define __SLIST_TESTS_HPP

#include "doctest.h"
#include <sstream>
#include "sint.hpp"
#include "slist.hpp"

SList SList1(SElement const& x) {
    return SList() << x;
}

SList SList2(SElement const& x,
             SElement const& y) {
    return SList1(x) << y;
}

TEST_CASE("Извеждане и събиране на елементи от дълбок списък") {
    SList sl = SList()
    << 
        SList2(SInt(1), SList1(SInt(2)))
    <<
        (SList()
            <<  SList2(SList1(SInt(3)), SInt(4))
            <<  SList2(SInt(5), SList1(SInt(6)))
            <<  SList()
            <<  SList1(SInt(7)))
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