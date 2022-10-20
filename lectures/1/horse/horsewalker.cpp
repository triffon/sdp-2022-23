#include "horsewalker.hpp"

HorseWalker::HorseWalker(size_t size) {
    initBoard(size);
}

void HorseWalker::initBoard(size_t size) {
    for(size_t i = 0; i < size; i++)
        board.push_back(ChessRow(size));
}

bool HorseWalker::insideBoard(Position const& pos) const {
    return pos.first >= 0  && pos.first < board.size() &&
           pos.second >= 0 && pos.second < board.size();
}