#include "Level2.h"

MoveInput Level2::getNextMove(Board& board) {
    auto& moves = board.getLegalMoves();
    std::vector<Move> captureChecks;
    captureChecks.reserve(moves.size());
    for (const Move& move : moves) {
        if (move.capturedPiece) {
            captureChecks.push_back(move);
        } else if (move.check) {
            captureChecks.push_back(move);
        }
    }
    return randomMove(captureChecks.size() ? captureChecks : moves);
}
