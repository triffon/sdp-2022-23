#ifndef __STACK_HORSEWALKER_HPP
#define __STACK_HORSEWALKER_HPP
#include "lstack.hpp"
#include "horsewalker.hpp"

using Walk = LinkedStack<Position>;

class StackHorseWalker : public HorseWalker {
private:
    Walk walk;
public:
    StackHorseWalker(size_t size = 8);
    bool existsWalk(Position const& start, Position const& end);
};


#endif