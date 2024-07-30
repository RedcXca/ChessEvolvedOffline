#include "ComputerLevel4.h"
#include "UnrecoverableChessException.h"
#include <algorithm>

MoveInput ComputerLevel4::getNextMove(Board& board) {
    auto moves = board.getLegalMoves();
    if (!moves.size()) throw UnrecoverableChessException("No moves possible");
    for (auto& move : moves) { // automatically play checkmates
        if (move.check) {
            board.makeMove(move);
            if (!board.generateLegalMoves().size()) {
                board.undoMove();
                board.generateLegalMoves();
                return {move.from, move.to, move.promotionPiece};
            }
            board.undoMove();
            board.generateLegalMoves();
        }
    }
    std::sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b) {
        return moveScore(board, a) > moveScore(board, b);
    });

    return {moves[0].from, moves[0].to, moves[0].promotionPiece};
}

int ComputerLevel4::moveScore(Board& board, Move move) {
    auto colorMap = board.checkThreatenedPieces(move.to);
    auto& mySide = colorMap[board.getSide()];
    auto& otherSide = colorMap[board.getNextColor(board.getSide())];
    std::erase(mySide, move.originalPiece);

    for (auto& pair : colorMap) {
        auto& pieces = pair.second;
        std::sort(pieces.begin(), pieces.end(), [](Piece* a, Piece* b) {
            return a->getValue() < b->getValue();
        });
    }

    int myGains = 0, otherGains = 0;

    if (move.capturedPiece) myGains += move.capturedPiece->getValue();
    if (otherSide.size()) otherGains += move.originalPiece->getValue();
    for (size_t i = 0; i < std::min(mySide.size(), otherSide.size() - 1); ++i) {
        myGains += otherSide[i]->getValue();
        otherGains += mySide[i]->getValue();
    }
    return (myGains - otherGains + CHECKWEIGHT * move.check) * (!move.promotionPiece || move.promotionPiece == 'Q'); // auto-queen
}

