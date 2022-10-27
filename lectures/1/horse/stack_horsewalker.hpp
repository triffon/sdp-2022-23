#ifndef __STACK_HORSEWALKER_HPP
#define __STACK_HORSEWALKER_HPP
#include "lstack.hpp"
#include "horsewalker.hpp"

using Walk = LinkedStack<Position>;

class StackHorseWalker : public HorseWalker {
private:
    HorseWalk hwalk;
    Walk walk;
public:
    StackHorseWalker(size_t size = 8);
    HorseWalk const& findWalk(Position const& start, Position const& end);
};


#endif