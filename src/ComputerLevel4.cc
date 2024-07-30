#include "ComputerLevel4.h"
#include <algorithm>

MoveInput ComputerLevel4::getNextMove(Board& board) {
    auto moves = board.getLegalMoves();
    for (auto& move : moves) { // automatically play checkmates
        if (move.check) {
            board.makeMove(move);
            if (!board.getLegalMoves().size()) {
                board.undoMove();
                return {move.from, move.to, move.promotionPiece};
            }
            board.undoMove();
        }
    }
    std::vector<std::pair<float, Move>> moveScores;
    for (const auto& move : moves) {
        float score = moveScore(board, move);
        moveScores.push_back({score, move});
    }
    auto maxScore = std::max_element(moveScores.begin(), moveScores.end(), [&](const auto& a, const auto& b) {
        return  a.first < b.first;
    });
    std::cout << "MaxScore: " << maxScore->first << std::endl;
    std::vector<Move> bestMoves;
    for (auto& move : moveScores) {
        if (std::fabs(move.first - maxScore->first) < 0.001f) bestMoves.push_back(move.second);
    }
    // for (auto& move : bestMoves) {
    //     moveScore(board, move, true);
    // }
    return randomMove(bestMoves);
}

float centralizationScore(Position p) {
    int centerX1 = 3, centerY1 = 3;
    int centerX2 = 4, centerY2 = 4;

    // Manhattan distance from the two central points
    float dis1 = std::abs(p.x - centerX1) + std::abs(p.y - centerY1);
    float dis2 = std::abs(p.x - centerX2) + std::abs(p.y - centerY2);
    float min = std::min(dis1, dis2);

    float max = 6.0; // Maximum possible Manhattan distance on an 8x8 board
    float centralizedValue = (1 - (min / max));

    return centralizedValue;
}

float ComputerLevel4::moveScore(Board& board, Move move, bool log) {
    int myGains = 0, otherGains = 0;
    if (move.capturedPiece) myGains += move.capturedPiece->getValue();
    board.makeMove(move);
    auto colorMap = board.checkThreatenedPieces(move.to);
    auto& otherSide = colorMap[board.getSide()];
    auto& mySide = colorMap[board.getNextColor(board.getSide())];

    for (auto& pair : colorMap) {
        auto& pieces = pair.second;
        std::sort(pieces.begin(), pieces.end(), [](Piece* a, Piece* b) {
            return a->getValue() < b->getValue();
        });
    }

    if (otherSide.size()) otherGains += move.originalPiece->getValue();
    for (int i = 0; i < std::min(std::ssize(mySide), std::ssize(otherSide) - 1); ++i) {
        myGains += otherSide[i]->getValue();
        otherGains += mySide[i]->getValue();
    }
    board.undoMove();
    if (log) std::cout << "Calculating centralization score from: " << move.from.toString() << " to " <<move.to.toString() << ": SCORE: " << (myGains - otherGains + CHECKWEIGHT * move.check + CENTRALIZATIONWEIGHT * (centralizationScore(move.to) - centralizationScore(move.from))) * (!move.promotionPiece || move.promotionPiece == 'Q') <<" MyGains: " << myGains << " OtherGains: " << otherGains << " Check: " << (move.check ? "true" : "false") << " Centralization To  " << centralizationScore(move.to) << " Centralization From " << centralizationScore(move.from) << std::endl;
    return (myGains - otherGains + CHECKWEIGHT * move.check + CENTRALIZATIONWEIGHT * (centralizationScore(move.to) - centralizationScore(move.from))) * (!move.promotionPiece || move.promotionPiece == 'Q'); // auto-queen
}

