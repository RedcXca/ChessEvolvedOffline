#include "Level3.h"

//UNIMPLEMENTED
MoveInput Level3::getNextMove(Board& board) {
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
