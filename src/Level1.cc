#include "Level1.h"

MoveInput Level1::getNextMove(Board& board) {
    return randomMove(board.getLegalMoves());
}
