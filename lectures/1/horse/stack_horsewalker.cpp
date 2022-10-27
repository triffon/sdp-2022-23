#include <cmath>
#include "stack_horsewalker.hpp"

StackHorseWalker::StackHorseWalker(size_t size) : HorseWalker(size) {}

HorseWalk const& StackHorseWalker::findWalk(Position const& start, Position const& end) {
    return hwalk;
    /*
    walk.push(start);
    while(!walk.empty()) {
        Position current = walk.peek();
        if (current == end)
            // успех
            return true;

        if (!insideBoard(current) || !insideBoard(end) || board[current.first][current.second])
            // стъпка назад
            walk.pop();
        else {
            // стъпка напред
            board[current.first][current.second] = true;
            for(int dx = -2; dx <= 2; dx++)
                if (dx != 0)
                    for (int sign : {-1, 1}) {
                        int dy = sign * (3 - std::abs(dx));
                        walk.push({current.first + dx, current.second + dy});
                    }
        }
    }

    return false;
    */
}