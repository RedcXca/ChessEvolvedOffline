#include "board.h"
#include <cmath>
#include <algorithm>
#include "queen.h"

void Board::undoMove() {
    Move lastMove = history.back();
    history.pop_back();
    board[lastMove.from.y][lastMove.from.x] = lastMove.originalPiece;
    if (lastMove.enPassant) { lastMove.to.y += lastMove.originalPiece->getColor() == Color::White ? -1 : 1; }
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

inline int signum(int x) { return (x > 0) - (x < 0); }

bool Board::checkBlocked(Position pos, int deltaX, int deltaY, bool attackable, Color otherSide) {
    for (int i = 1; i <= std::max(std::abs(deltaX), std::abs(deltaY))-1; ++i)
        if (board[pos.y + i * signum(deltaY)][pos.x + i * signum(deltaX)]) return true;
    if (board[pos.y + deltaY][pos.x + deltaX] && board[pos.y + deltaY][pos.x + deltaX]->getColor() == otherSide) return attackable;
    return false;
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
                            if (checkBlocked({j, i}, move.deltaX, move.deltaY)) continue;
                        }
                        threatened[board[i][j]->getColor()]++;
                    }
    return threatened;
}

bool Board::validateBoard(Color side) { return !checkThreatened(kingPositions[side])[side]; }

void Board::testMove(Move move) {
    history.push_back(move);
    board[move.to.y][move.to.x] = move.originalPiece;
    board[move.from.y][move.from.x] = nullptr;
    if (move.enPassant) {
        board[move.to.y][move.to.x] = nullptr;
        board[move.to.y + (move.originalPiece->getColor() == Color::White ? -1 : 1)][move.to.x] = nullptr;
    }
    if (move.originalPiece->toChar() == 'K' || move.originalPiece->toChar() == 'k') {
        kingPositions[move.originalPiece->getColor()] = move.to;
        if (move.to.x - move.from.x == 2) {
            board[move.to.y][move.to.x - 1] = board[move.to.y][move.to.x + 1];
            board[move.to.y][move.to.x + 1] = nullptr;
        } else if (move.to.x - move.from.x == -2) {
            board[move.to.y][move.to.x + 1] = board[move.to.y][move.to.x - 2];
            board[move.to.y][move.to.x - 2] = nullptr;
        }
    }
}
void Board::makeMove(Move move) {
    testMove(move);
    //handle Promotion creation here
}

std::list<Move> Board::generateLegalMoves(Color side) {
    Color otherSide = side == Color::White ? Color::Black : Color::White;
    std::list<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] && board[i][j]->getColor() == side) {
                auto possibleMoves = board[i][j]->getPossibleMoves();
                for (auto move : possibleMoves) {
                    int x = j + move.deltaX;
                    int y = i + move.deltaY;
                    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                        if (!board[y][x] || board[y][x]->getColor() != side) {
                            if (move.type == MoveType::MoveOnly) {
                                if (!checkBlocked({j, i}, move.deltaX, move.deltaY)) {
                                    moves.push_back({{j, i}, {x, y}, board[i][j], nullptr});
                                }
                            }
                            if (move.type == MoveType::MoveOrAttack) {
                                if (!checkBlocked({j, i}, move.deltaX, move.deltaY, true, otherSide)) {
                                    moves.push_back({{j, i}, {x, y}, board[i][j], board[y][x]});
                                }
                            }
                            if (move.type == MoveType::AttackOnly){
                                if (board[y][x] && board[y][x]->getColor() == otherSide) {
                                    if (!checkBlocked({j, i}, move.deltaX, move.deltaY, true, otherSide)) {
                                        moves.push_back({{j, i}, {x, y}, board[i][j], board[y][x]});
                                    }
                                }
                            }
                            if (move.type == MoveType::UnblockableMoveOrAttack) {
                                moves.push_back({{j, i}, {x, y}, board[i][j], board[y][x]});
                            }
                            if (move.type == MoveType::Teleport) {
                                if (!board[y][x]) moves.push_back({{j, i}, {x, y}, board[i][j], nullptr});
                            }
                            if (move.type == MoveType::UnblockableAttackOnly){
                                if (board[y][x] && board[y][x]->getColor() == otherSide) {
                                    moves.push_back({{j, i}, {x, y}, board[i][j], board[y][x]});
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (auto move:moves) {
        testMove(move);
        if (checkThreatened(kingPositions[side])[otherSide]) {
            moves.remove(move);
        }
        undoMove();
    }
    return moves;
}
