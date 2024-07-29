#include "Level1.h"

MoveInput Level1::getNextMove(Board& board) {
    std::vector<Move> moves = board.generateLegalMoves(color);
    return randomMove(moves);
}
