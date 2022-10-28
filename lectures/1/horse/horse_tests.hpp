#include <iostream>
#include "doctest.h"
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

TEST_CASE_TEMPLATE("На дъска 4x4 всички позиции да достижими от (0,0)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    size_t SIZE = 4;
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++) {
            AnyHorseWalker horseWalker(SIZE);
            // std::clog << "Търсим разходка до (" << i << "," << j << ")\n";
            CHECK(horseWalker.existsWalk({0, 0}, {i, j}));
        }
}


// TODO: да преизползваме HorseWalker::insideBoard
// TODO: isValid* функциите да се преместят в отделен source файл
// с помощни функции (utils.cpp)
bool isValidPosition(Position const& pos, size_t boardSize) {
    return pos.first >= 0  && pos.first < boardSize &&
           pos.second >= 0 && pos.second < boardSize;
}

bool isValidMove(Position const& from, Position const& to, size_t boardSize) {
    return isValidPosition(from, boardSize) &&
           isValidPosition(to, boardSize) &&
            std::abs(to.first - from.first) == 2 &&
           std::abs(to.second - from.second) == 1
           ||
           std::abs(to.first - from.first) == 1 &&
           std::abs(to.second - from.second) == 2;
}

bool isValidWalk(HorseWalk const& walk, size_t boardSize,
                 Position const& from, Position const& to) {

    std::clog << "Проверявам разходка на коня:" << std::endl;
    std::clog << walk;
    // !!! for(Position p : walk)
    if (walk.empty() ||
        walk[0] != from || walk[walk.size() - 1] != to)
        return false;

    int i = 0;
    while(i < walk.size() - 1 && isValidMove(walk[i], walk[i+1], boardSize))
        i++;
    // i == walk.size() - 1 || !isValidMove(walk[i], walk[i+1])
    return i == walk.size() - 1;
}

TEST_CASE_TEMPLATE("На дъска 4x4 намираме правилна разходка от (0,0) до (3,3)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    Position from{0, 0}, to{3, 3};
    CHECK(isValidWalk(horseWalker.findWalk(from, to), 4, from, to));
}

TEST_CASE_TEMPLATE("На дъска 4x4 намираме правилна разходка от (0,0) до (2,2)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    AnyHorseWalker horseWalker(4);
    Position from{0, 0}, to{2, 2};
    CHECK(isValidWalk(horseWalker.findWalk(from, to), 4, from, to));
}

TEST_CASE_TEMPLATE("На дъска 4x4 за всички позиции намираме правилна разходка от (0,0)",
                    AnyHorseWalker, RecursiveHorseWalker, StackHorseWalker) {
    size_t SIZE = 4;
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++) {
            AnyHorseWalker horseWalker(SIZE);
            // std::clog << "Търсим разходка до (" << i << "," << j << ")\n";
            CHECK(isValidWalk(horseWalker.findWalk({0, 0}, {i, j}), SIZE, {0, 0}, {i, j}));
        }
}

