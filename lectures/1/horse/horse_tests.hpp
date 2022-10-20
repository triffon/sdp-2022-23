#include "recursive_horsewalker.hpp"

TEST_CASE_TEMPLATE("На дъска 4x4 можем да стигнем от (0,0) до (3,3)",
                    AnyHorseWalker, RecursiveHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK(horseWalker.existsWalk({0, 0}, {3, 3}));
}