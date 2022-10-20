#ifndef __HORSE_WALKER
#define __HORSE_WALKER
#include <utility>

using Position = std::pair<int, int>;

class HorseWalker {
public:
    virtual bool existsWalk(Position const& start, Position const& end) const = 0;
    virtual ~HorseWalker() {}
};

#endif