#include "ComputerLevel5.h"
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include "Evaluator.h"
#include <random>

namespace {
    constexpr int MAX_DEPTH = 3;

    std::unordered_map<char, Evaluator> evaluators;

    inline int mvv_lva(const Move& move) {
        return move.capturedPiece ? move.capturedPiece->getValue() - move.originalPiece->getValue() : -1;
    }

    int evaluateState(Board& board) {
        int evaluation = 0;
        for (int y = 0; y < Board::SIZE; ++y)
            for (int x = 0; x < Board::SIZE; ++x)
                if (auto piece = board.getPiece(Position{x, y})) {
                    char upperChar = std::toupper(piece->toChar());
                    if (!evaluators.count(upperChar)) evaluators.emplace(upperChar, Evaluator{upperChar});
                    int score = piece->getValue() * 100 + evaluators.at(upperChar).getEval(Position{x, y}, piece->getColor());
                    evaluation += score * (piece->getColor() == board.getSide() ? 1 : -1);
                }
        return evaluation;
    }
};

int ComputerLevel5::minimax(Board& board, int depth, bool maximize, int alpha = -INT_MAX, int beta = INT_MAX) {
    int multiplier = board.getSide() == color ? 1 : -1;
    if (board.getLegalMoves().empty()) { // Game over
        if (board.validateBoard(board.getSide())) return 0; // Draw has neutral value
        return -multiplier * (1000000000 + depth * 10); // checkmate is worth more when reached in less moves
    }
    if (!depth) return multiplier * evaluateState(board);
    int bestEval = maximize ? INT_MIN : INT_MAX;
    std::vector<Move> categorizedMoves[2];
    for (auto move : board.getLegalMoves())
        categorizedMoves[!move.capturedPiece].push_back(move);
    std::sort(categorizedMoves[0].begin(), categorizedMoves[0].end(), [](auto& m1, auto& m2) {
        return mvv_lva(m1) > mvv_lva(m2);
    });
    for (const auto& moves : categorizedMoves)
        for (const auto& move : moves) {
            if (alpha >= beta) return bestEval;
            board.makeMove(move);
            int nextEval = minimax(board, depth - 1, !maximize, alpha, beta);
            board.undoMove();
            if (maximize) {
                bestEval = std::max(bestEval, nextEval);
                alpha = std::max(alpha, bestEval);
            } else {
                bestEval = std::min(bestEval, nextEval);
                beta = std::min(beta, bestEval);
            }
        }
    return bestEval;
}

MoveInput ComputerLevel5::getNextMove(Board& board) {
    if (auto& moveHistory = board.getMoveHistory(); moveHistory.size())
        openingBook.filterOpenings({moveHistory.back().from, moveHistory.back().to});
    if (auto& possibleOpenings = openingBook.getOpenings(); possibleOpenings.size()) {
        auto move = possibleOpenings[std::uniform_int_distribution<>(0, possibleOpenings.size() - 1)(gen)][openingBook.getMoveIndex()];
        openingBook.filterOpenings(move);
        return {move.first, move.second};
    }
    auto moves = board.getLegalMoves();
    int bestScore = INT_MIN;
    std::vector<Move> bestMoves;
    for (auto move : moves) {
        board.makeMove(move);
        int score = minimax(board, MAX_DEPTH - 1, false);
        board.undoMove();
        if (score > bestScore) {
            bestScore = score;
            bestMoves.clear();
            bestMoves.push_back(move);
        } else if (score == bestScore) bestMoves.push_back(move);
    }
    return randomMove(bestMoves);
}
