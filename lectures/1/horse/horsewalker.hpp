#ifndef __HORSE_WALKER
#define __HORSE_WALKER
#include <cstddef>
#include <utility>
#include <vector>

using Position = std::pair<int, int>;
// TODO: да се реализира чрез std::array
using ChessRow   = std::vector<bool>;
using ChessBoard = std::vector<ChessRow>;

class HorseWalker {
protected:
    ChessBoard board;
    void initBoard(size_t size);
    bool insideBoard(Position const& pos) const;
public:
    HorseWalker(size_t size = 8);

    // проверява дали има разходка на коня от start до end
    virtual bool existsWalk(Position const& start, Position const& end) = 0;
    virtual ~HorseWalker() {}
};

#endif