#ifndef __QUEUE_HORSEWALKER_HPP
#define __QUEUE_HORSEWALKER_HPP

#include "horsewalker.hpp"
#include "lqueue.hpp"
#include "lstack.hpp"

using Step = std::pair<Position, Position>;

class QueueHorseWalker : public HorseWalker {
    LinkedQueue<Position> horseWave;
    HorseWalk walk;
    LinkedStack<Step> steps;
public:
    QueueHorseWalker(size_t size) : HorseWalker(size) {}

    // намира разходка на коня от start до end
    // връща празна разходка, ако не съществува
    virtual HorseWalk const& findWalk(Position const& start, Position const& end);
};

#endif 