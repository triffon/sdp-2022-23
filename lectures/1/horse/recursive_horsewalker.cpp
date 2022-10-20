#include <cmath>
#include "recursive_horsewalker.hpp"

RecursiveHorseWalker::RecursiveHorseWalker(size_t size) : HorseWalker(size) {}

bool RecursiveHorseWalker::existsWalk(Position const& start, Position const& end) {
    if (!insideBoard(start) || !insideBoard(end) || board[start.first][start.second])
        // стъпка назад
        return false;

    if (start == end)
        // успех
        return true;

    // стъпка напред
    board[start.first][start.second] = true;

    for(int dx = -2; dx <= 2; dx++)
        if (dx != 0)
            for (int sign : {-1, 1}) {
                int dy = sign * (3 - std::abs(dx));
                if (existsWalk({start.first + dx, start.second + dy}, end))
                    // успех
                    return true; 
            }

    // стъпка назад
    return false;
}