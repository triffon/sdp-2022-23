#include <cmath>
#include "recursive_horsewalker.hpp"

RecursiveHorseWalker::RecursiveHorseWalker(size_t size) : HorseWalker(size) {}

HorseWalk const& RecursiveHorseWalker::findWalk(Position const& start, Position const& end) {
    findWalkHelper(start, end);
    return walk;
}

bool RecursiveHorseWalker::findWalkHelper(Position const& start, Position const& end) {
    if (!insideBoard(start) || !insideBoard(end) ||
        board[start.first][start.second]) {
        // стъпка назад
        return false;
    }

    // стъпка напред
    board[start.first][start.second] = true;

    walk.push_back(start);

    if (start == end)
        // успех
        return true;

    for(int dx = -2; dx <= 2; dx++)
        if (dx != 0)
            for (int sign : {-1, 1}) {
                int dy = sign * (3 - std::abs(dx));
                if (findWalkHelper({start.first + dx, start.second + dy}, end))
                    // успех
                    return true; 
            }

    // стъпка назад
    walk.pop_back();
    return false;
}