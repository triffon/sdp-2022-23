#ifndef __STACK_HORSEWALKER_HPP
#define __STACK_HORSEWALKER_HPP
#include "lstack.hpp"
#include "horsewalker.hpp"

class StackHorseWalker : public HorseWalker {
public:
    StackHorseWalker(size_t size = 8);
    bool existsWalk(Position const& start, Position const& end);
};


#endif