#include "ComputerLevel3.h"

// TODO: UNIMPLEMENTED
MoveInput ComputerLevel3::getNextMove(Board& board) {
    auto& moves = board.getLegalMoves();
    std::vector<Move> avoidCaptures;
    avoidCaptures.reserve(moves.size());
    std::vector<Move> captureChecks;
    captureChecks.reserve(moves.size());
    for (const Move& move : moves) {
        int priorThreats = board.checkThreatened(move.from).at(board.getNextColor(board.getSide()));
        board.makeMove(move);
        int postThreats = board.checkThreatened(move.to).at(board.getSide());
        board.undoMove();
        if (postThreats < priorThreats) {
            avoidCaptures.push_back(move);
        } else if (move.capturedPiece) {
            captureChecks.push_back(move);
        } else if (move.check) {
            captureChecks.push_back(move);
        }
    }
    return randomMove(avoidCaptures.size() ? avoidCaptures : captureChecks.size() ? captureChecks : moves);
}
