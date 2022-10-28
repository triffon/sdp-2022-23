#ifndef __HORSE_WALKER
#define __HORSE_WALKER
#include <cstddef>
#include <utility>
#include <vector>
#include <iostream>

using Position = std::pair<int, int>;
// TODO: да се реализира чрез std::array
using ChessRow   = std::vector<bool>;
using ChessBoard = std::vector<ChessRow>;
using HorseWalk  = std::vector<Position>;

class HorseWalker {
protected:
    ChessBoard board;
    void initBoard(size_t size);
    bool insideBoard(Position const& pos) const;
public:
    HorseWalker(size_t size = 8);

    // проверява дали има разходка на коня от start до end
    virtual bool existsWalk(Position const& start, Position const& end);
    
    // намира разходка на коня от start до end
    // връща празна разходка, ако не съществува
    virtual HorseWalk const& findWalk(Position const& start, Position const& end) = 0;
    virtual ~HorseWalker() {}
};

std::ostream& operator<<(std::ostream& os, Position const& pos);
std::ostream& operator<<(std::ostream& os, HorseWalk const& walk);

#endif