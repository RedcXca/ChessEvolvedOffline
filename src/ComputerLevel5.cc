#include "ComputerLevel5.h"
#include <climits>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <cctype>
#include "Evaluator.h"
#include <chrono>

constexpr int MAX_DEPTH = 3;

namespace {
    std::unordered_map<char, Evaluator> evaluators;
};

int evaluateState(Board& board) {
    int evaluation = 0;
    for (int y = 0; y < Board::SIZE; ++y)
        for (int x = 0; x < Board::SIZE; ++x)
            if (auto piece = const_cast<Piece*>(board.getPiece(Position{x, y}))) { // TODO: fix const
                char upperChar = std::toupper(piece->toChar());
                if (!evaluators.count(upperChar)) evaluators.emplace(upperChar, Evaluator{upperChar});
                int score = piece->getValue() * 100 + evaluators.at(upperChar).getEval(Position{x, y}, piece->getColor());
                evaluation += score * (piece->getColor() == board.getSide() ? 1 : -1);
            }
    return evaluation;
}

int positions, bot;
int ComputerLevel5::minimax(Board& board, int depth, bool maximize, int alpha = -INT_MAX, int beta = INT_MAX) {
    ++positions;
    int multiplier = board.getSide() == color ? 1 : -1;
    if (!board.getLegalMoves().size()) {
        if (!board.validateBoard(board.getSide())) return -multiplier * INT_MAX;
        return 0;
    }
    if (!depth) {
        ++bot;
        return multiplier * evaluateState(board);
    }
    int bestEval = maximize ? INT_MIN : INT_MAX;
    auto moves = board.getLegalMoves();
    for (auto move : moves) {
        if (alpha >= beta) break;
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
    positions = bot = 0;
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
    std::cout << positions << ' ' << bot << ' ' << bestMoves.size() << '\n';
    std::cout << bestScore << '\n';
    for (auto& move : bestMoves)
        std::cout << move.from.toString() << ' ' << move.to.toString() << std::endl;
    return randomMove(bestMoves);
}
