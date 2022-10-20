#ifndef __RECURSIVE_HORSE_WALKER
#define __RECURSIVE_HORSE_WALKER
#include "horsewalker.hpp"

class RecursiveHorseWalker : public HorseWalker {
public:
    RecursiveHorseWalker(size_t size = 8);
    bool existsWalk(Position const& start, Position const& end);
};

#endif