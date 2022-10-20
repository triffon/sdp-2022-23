#include "recursive_horsewalker.hpp"
#include "stack_horsewalker.hpp"

TYPE_TO_STRING(RecursiveHorseWalker);
TYPE_TO_STRING(StackHorseWalker);

TEST_CASE_TEMPLATE("Никъде не можем да стигнем от невалидна стартова позиция",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK_FALSE(horseWalker.existsWalk({-1, 0}, {3, 3}));
}

TEST_CASE_TEMPLATE("Не можем да стигнем до невалидна крайна позиция",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK_FALSE(horseWalker.existsWalk({0, 0}, {3, 5}));
}

TEST_CASE_TEMPLATE("Началната и крайната позиция съвпадат",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK(horseWalker.existsWalk({0, 0}, {0, 0}));
}

TEST_CASE_TEMPLATE("На дъска 4x4 можем да стигнем от (0,0) до (3,3)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK(horseWalker.existsWalk({0, 0}, {3, 3}));
}

TEST_CASE_TEMPLATE("На дъска 4x4 можем да стигнем от (0,0) до (2,2)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK(horseWalker.existsWalk({0, 0}, {2, 2}));
}

TEST_CASE_TEMPLATE("На дъска 4x4 можем да стигнем от (0,0) до (0,1)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    CHECK(horseWalker.existsWalk({0, 0}, {0, 1}));
}

TEST_CASE_TEMPLATE("На дъска 3x3 не можем да стигнем от (0,0) до (1,1)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(3);
    CHECK_FALSE(horseWalker.existsWalk({0, 0}, {1, 1}));
}