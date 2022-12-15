#include "doctest.h"

#include <sstream>
#include "tree.hpp"

using IntTree = Tree<int>;

TEST_CASE("Извеждане на примерно дърво на две нива") {
    IntTree t =
        IntTree(1)
                << IntTree(2)
                << IntTree(9)
                << IntTree(10);

    std::ostringstream os;
    t.print(os);
    CHECK_EQ(os.str(), "(1 (2) (9) (10))");
}