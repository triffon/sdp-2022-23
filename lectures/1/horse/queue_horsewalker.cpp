#include "queue_horsewalker.hpp"

HorseWalk const& QueueHorseWalker::findWalk(Position const& start, Position const& end) {
    if (!insideBoard(end))
        return walk;
    horseWave.enqueue(start);
    while (!horseWave.empty()) {
        Position current = horseWave.dequeue();
        if (current == end) {
            // успех
            LinkedStack<Position> reversedWalk;

            while (!steps.empty()) {
                Step step = steps.pop();
                if (step.second == current) {
                    reversedWalk.push(current);
                    current = step.first;
                }
            }
            reversedWalk.push(start);
            while (!reversedWalk.empty())
                walk.push_back(reversedWalk.pop());
            return walk;
        }

        if (insideBoard(current) && !board[current.first][current.second]) {
            // стъпваме на тази позиция
            board[current.first][current.second] = true;
            // добавяме всички следващи стъпки
            for(int dx = -2; dx <= 2; dx++)
                if (dx != 0)
                    for (int sign : {-1, 1}) {
                        int dy = sign * (3 - std::abs(dx));
                        Position newPosition{current.first + dx, current.second + dy};
                        horseWave.enqueue(newPosition);
                        steps.push({current, newPosition});
                    }
        }
    }
    // не успяхме да стигнем до края
    return walk;
}
