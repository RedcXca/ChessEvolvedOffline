#include "board.h"
#include <cmath>
#include <algorithm>

void Board::undoMove() {
    Move lastMove = history.back();
    history.pop_back();
    board[lastMove.from.y][lastMove.from.x] = lastMove.originalPiece;
    if (lastMove.enPassant) {
        lastMove.to.y += lastMove.originalPiece->getColor() == Color::White ? -1 : 1;
    }
    board[lastMove.to.y][lastMove.to.x] = lastMove.capturedPiece;
    if (lastMove.originalPiece->toChar() == 'K' || lastMove.originalPiece->toChar() == 'k') {
        if (lastMove.to.x - lastMove.from.x == 2) {
            board[lastMove.to.y][lastMove.to.x + 1] = board[lastMove.to.y][lastMove.to.x - 1];
            board[lastMove.to.y][lastMove.to.x - 1] = nullptr;
        } else if (lastMove.to.x - lastMove.from.x == -2) {
            board[lastMove.to.y][lastMove.to.x - 2] = board[lastMove.to.y][lastMove.to.x + 1];
            board[lastMove.to.y][lastMove.to.x + 1] = nullptr;
        }
    }
    // Promotion logic should be already covered by this, assuming the Game, not the Board, stores the smart pointers for the pieces
}

inline int signum(int x) {
    return x ? x < 0 ? -1 : 1 : 0;
}

std::map<Color, int> Board::checkThreatened(Position pos) {
    std::map<Color, int> threatened;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j])
                for (auto move : board[i][j]->getPossibleMoves())
                    if (i + move.deltaY == pos.y && j + move.deltaX == pos.x) {
                        if (move.type == MoveType::MoveOnly || move.type == MoveType::Teleport) continue;
                        if (move.type == MoveType::AttackOnly || move.type == MoveType::MoveOrAttack) {
                            bool blocked = false;
                            for (int k = 1; k <= std::max(std::abs(move.deltaX), std::abs(move.deltaY)); ++k)
                                if (board[i + k * signum(move.deltaX)][j + k * signum(move.deltaY)]) {
                                    blocked = true;
                                    break;
                                }
                            if (blocked) continue;
                        }
                        threatened[board[i][j]->getColor()]++;
                    }
    return threatened;
}

bool Board::validateBoard(Color side) {
    return !checkThreatened(kingPositions[side])[side];
}

void Board::makeMove(Move move) {
    history.push_back(move);
    board[move.to.y][move.to.x] = move.originalPiece;
    board[move.from.y][move.from.x] = nullptr;
    if (move.enPassant) {
        board[move.to.y][move.to.x] = nullptr;
        board[move.to.y + (move.originalPiece->getColor() == Color::White ? -1 : 1)][move.to.x] = nullptr;
    }
    if (move.originalPiece->toChar() == 'K' || move.originalPiece->toChar() == 'k') {
        if (move.to.x - move.from.x == 2) {
            board[move.to.y][move.to.x - 1] = board[move.to.y][move.to.x + 1];
            board[move.to.y][move.to.x + 1] = nullptr;
        } else if (move.to.x - move.from.x == -2) {
            board[move.to.y][move.to.x + 1] = board[move.to.y][move.to.x - 2];
            board[move.to.y][move.to.x - 2] = nullptr;
        }
    }
    if (move.promotionPiece) {
        board[move.to.y][move.to.x] = move.promotionPiece;
    }
}
