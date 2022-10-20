#include <cmath>
#include "stack_horsewalker.hpp"

StackHorseWalker::StackHorseWalker(size_t size) : HorseWalker(size) {}

bool StackHorseWalker::existsWalk(Position const& start, Position const& end) {
    return false;
    if (!insideBoard(start) || !insideBoard(end) || board[start.first][start.second])
        return false;

    if (start == end)
        return true;

    board[start.first][start.second] = true;

    for(int dx = -2; dx <= 2; dx++)
        if (dx != 0)
            for (int sign : {-1, 1}) {
                int dy = sign * (3 - std::abs(dx));
                if (existsWalk({start.first + dx, start.second + dy}, end))
                    return true; 
            }

    return false;
}