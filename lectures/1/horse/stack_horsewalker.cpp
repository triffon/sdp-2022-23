#include <cmath>
#include "stack_horsewalker.hpp"

StackHorseWalker::StackHorseWalker(size_t size) : HorseWalker(size) {}

HorseWalk const& StackHorseWalker::findWalk(Position const& start, Position const& end) {
    StackFrame startFrame;
    startFrame.push(start);
    stack.push(startFrame);
    while(!stack.empty()) {
        StackFrame& currentFrame = stack.peek();
        if (currentFrame.empty())
            stack.pop();
        else {
            Position current = currentFrame.peek();
            if (current == end) {
                // успех
                StackFrame reversedWalk;
                while (!stack.empty())
                    reversedWalk.push(stack.pop().peek());
                while (!reversedWalk.empty())
                    walk.push_back(reversedWalk.pop());
                return walk;
            }

            if (!insideBoard(current) || !insideBoard(end) || board[current.first][current.second])
                // стъпка назад
                currentFrame.pop();
            else {
                // стъпка напред
                // правим си нова стекова рамка
                StackFrame newFrame;
                board[current.first][current.second] = true;
                for(int dx = -2; dx <= 2; dx++)
                    if (dx != 0)
                        for (int sign : {-1, 1}) {
                            int dy = sign * (3 - std::abs(dx));
                            Position newPosition{current.first + dx, current.second + dy};
                            newFrame.push(newPosition);
                        }
                stack.push(newFrame);
            }
        }
    }

    return walk;
}