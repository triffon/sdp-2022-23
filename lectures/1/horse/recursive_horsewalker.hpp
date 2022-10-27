#ifndef __RECURSIVE_HORSE_WALKER
#define __RECURSIVE_HORSE_WALKER
#include "horsewalker.hpp"

class RecursiveHorseWalker : public HorseWalker {
    HorseWalk walk;
public:
    RecursiveHorseWalker(size_t size = 8);
    HorseWalk const& findWalk(Position const& start, Position const& end);
    bool findWalkHelper(Position const& start, Position const& end);
};

#endif