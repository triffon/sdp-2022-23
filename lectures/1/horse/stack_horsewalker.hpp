#ifndef __STACK_HORSEWALKER_HPP
#define __STACK_HORSEWALKER_HPP
#include "lstack.hpp"
#include "horsewalker.hpp"

using StackFrame = LinkedStack<Position>;
using HorseStack = LinkedStack<StackFrame>;

class StackHorseWalker : public HorseWalker {
private:
    HorseStack stack;
    HorseWalk walk;
public:
    StackHorseWalker(size_t size = 8);
    HorseWalk const& findWalk(Position const& start, Position const& end);
};


#endif