#include "ComputerLevel1.h"

MoveInput ComputerLevel1::getNextMove(Board& board) {
    return randomMove(board.getLegalMoves());
}
