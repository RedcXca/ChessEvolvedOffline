#include "ComputerLevel2.h"

MoveInput ComputerLevel2::getNextMove(Board& board) {
    auto& moves = board.getLegalMoves();
    std::vector<Move> priorityMoves;
    priorityMoves.reserve(moves.size());
    for (const Move& move : moves)
        if (move.capturedPiece || move.check)
            priorityMoves.push_back(move);
    return randomMove(priorityMoves.size() ? priorityMoves : moves);
}
