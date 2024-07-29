#include "ComputerLevel3.h"

// TODO: UNIMPLEMENTED
MoveInput ComputerLevel3::getNextMove(Board& board) {
    auto& moves = board.getLegalMoves();
    std::vector<Move> priorityMoves;
    priorityMoves.reserve(moves.size());
    for (const Move& move : moves) {
        if (move.capturedPiece) {
            priorityMoves.push_back(move);
        } else if (move.check) {
            priorityMoves.push_back(move);
        }
    }
    return randomMove(priorityMoves.size() ? priorityMoves : moves);
}
