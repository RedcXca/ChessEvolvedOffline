#include "Board.h"
#include <cmath>
#include <algorithm>
#include "angel.h"
#include "axeman.h"
#include "bishop.h"
#include "cougar.h"
#include "demon.h"
#include "fencer.h"
#include "ghost.h"
#include "hippo.h"
#include "imp.h"
#include "juggernaut.h"
#include "king.h"
#include "knight.h"
#include "legionary.h"
#include "moat.h"
#include "orc.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "rossevans.h"
#include "shinobi.h"
#include "thief.h"
#include "unicorn.h"
#include "valkyrie.h"
#include "warrior.h"
#include "wyvern.h"
#include "zebra.h"

void Board::undoMove() {
    Move lastMove = history.back();
    history.pop_back();
    board[lastMove.from.y][lastMove.from.x] = lastMove.originalPiece; // reset original piece
    if (lastMove.originalPiece->toChar() != board[lastMove.to.y][lastMove.to.x]->toChar()) {
        allPieces.pop_back(); // this means promotion went through, it's a move not a test
    }
    if (lastMove.enPassantPos == lastMove.to) { lastMove.to.y += lastMove.originalPiece->getColor() == Color::White ? -1 : 1; } // adjust position of captured piece for en passant
    board[lastMove.to.y][lastMove.to.x] = lastMove.capturedPiece;
    if (std::tolower(lastMove.originalPiece->toChar()) == 'k') {
        kingPositions[lastMove.originalPiece->getColor()] = lastMove.from;
        if (lastMove.to.x - lastMove.from.x == 2) {                                            // O-O
            board[lastMove.to.y][lastMove.to.x + 1] = board[lastMove.to.y][lastMove.to.x - 1]; // move rook back
            board[lastMove.to.y][lastMove.to.x - 1] = nullptr;                                 // empty rook's previous location
            board[lastMove.to.y][lastMove.to.x + 1]->setHasMoved(false);                       // reset rook's hasMoved
        } else if (lastMove.to.x - lastMove.from.x == -2) {                                    // O-O-O
            board[lastMove.to.y][lastMove.to.x - 2] = board[lastMove.to.y][lastMove.to.x + 1]; // move rook back
            board[lastMove.to.y][lastMove.to.x + 1] = nullptr;                                 // empty rook's previous location
            board[lastMove.to.y][lastMove.to.x - 2]->setHasMoved(false);                       // reset rook's hasMoved
        }
    }
    if (lastMove.firstMove) lastMove.originalPiece->setHasMoved(false); // reset hasMoved if it was the first move
}

inline int signum(int x) { return (x > 0) - (x < 0); }

bool Board::checkBlocked(Position pos, int deltaX, int deltaY, bool attackable, Color otherSide) {
    for (int i = 1; i < std::max(std::abs(deltaX), std::abs(deltaY)); ++i) // go up to one before the target square
        if (board[pos.y + i * signum(deltaY)][pos.x + i * signum(deltaX)]) return true;
    if (board[pos.y + deltaY][pos.x + deltaX] && board[pos.y + deltaY][pos.x + deltaX]->getColor() == otherSide) return !attackable; // there is a piece there to be attacked
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

bool Board::validateBoard(Color side) { return !checkThreatened(kingPositions[side])[Color(!int(side))]; }

void Board::testMove(Move move) {
    history.push_back(move);
    board[move.to.y][move.to.x] = move.originalPiece;
    board[move.from.y][move.from.x] = nullptr;
    if (move.enPassantPos == move.to) {
        board[move.to.y + (move.originalPiece->getColor() == Color::White ? -1 : 1)][move.to.x] = nullptr;
    }
    if (std::tolower(move.originalPiece->toChar()) == 'k') {
        kingPositions[move.originalPiece->getColor()] = move.to;
        if (move.to.x - move.from.x == 2) { // O-O
            board[move.to.y][move.to.x - 1] = board[move.to.y][move.to.x + 1];
            board[move.to.y][move.to.x + 1] = nullptr;
            board[move.to.y][move.to.x - 1]->setHasMoved(true);
        } else if (move.to.x - move.from.x == -2) { // O-O-O
            board[move.to.y][move.to.x + 1] = board[move.to.y][move.to.x - 2];
            board[move.to.y][move.to.x - 2] = nullptr;
            board[move.to.y][move.to.x + 1]->setHasMoved(true);
        }
    }
    move.originalPiece->setHasMoved(true);
}
void Board::makeMove(Move move) {
    testMove(move);
    if (std::tolower(move.originalPiece->toChar()) == 'p' && std::abs(move.to.y - move.from.y) == 2) {
        enPassantSquare = Position(move.to.x, move.to.y + (move.originalPiece->getColor() == Color::White ? -1 : 1));
    } else {
        enPassantSquare = Position(-1, -1); // default en passant square
    }
    if (move.promotionPiece == 'Q') {
        allPieces.push_back(std::make_unique<Queen>(move.originalPiece->getColor()));
        board[move.to.y][move.to.x] = allPieces.back().get();
    } else if (move.promotionPiece == 'R') {
        allPieces.push_back(std::make_unique<Rook>(move.originalPiece->getColor()));
        board[move.to.y][move.to.x] = allPieces.back().get();
    } else if (move.promotionPiece == 'B') {
        allPieces.push_back(std::make_unique<Bishop>(move.originalPiece->getColor()));
        board[move.to.y][move.to.x] = allPieces.back().get();
    } else if (move.promotionPiece == 'N') {
        allPieces.push_back(std::make_unique<Knight>(move.originalPiece->getColor()));
        board[move.to.y][move.to.x] = allPieces.back().get();
    }
}

std::vector<Move> Board::generateLegalMoves(Color side) {
    Color otherSide = side == Color::White ? Color::Black : Color::White;
    std::vector<Move> moves;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] && board[i][j]->getColor() == side) {
                auto possibleMoves = board[i][j]->getPossibleMoves();
                for (auto move : possibleMoves) {
                    int x = j + move.deltaX;
                    int y = i + move.deltaY;
                    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
                        if (move.type == MoveType::MoveOnly) {
                            if (!checkBlocked({j, i}, move.deltaX, move.deltaY)) {
                                moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], nullptr, enPassantSquare));
                            }
                        } else if (move.type == MoveType::MoveOrAttack) {
                            if (!checkBlocked({j, i}, move.deltaX, move.deltaY, true, otherSide)) {
                                moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y][x], enPassantSquare));
                            }
                        } else if (move.type == MoveType::AttackOnly) {
                            if (board[y][x] && board[y][x]->getColor() == otherSide) {
                                if (!checkBlocked({j, i}, move.deltaX, move.deltaY, true, otherSide)) {
                                    moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y][x], enPassantSquare));
                                }
                            } else if (std::tolower(board[i][j]->toChar()) == 'p') {
                                if (enPassantSquare == Position(x, y)) {
                                    moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y + (side == Color::White ? -1 : 1)][x], enPassantSquare));
                                }
                            }
                        } else if (move.type == MoveType::UnblockableMoveOrAttack) {
                            moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y][x], enPassantSquare));
                        } else if (move.type == MoveType::Teleport) {
                            if (!board[y][x]) moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], nullptr, enPassantSquare));
                        } else if (move.type == MoveType::UnblockableAttackOnly) {
                            if (board[y][x] && board[y][x]->getColor() == otherSide) {
                                moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y][x], enPassantSquare));
                            }
                        }
                    }
                }
                if (std::tolower(board[i][j]->toChar()) == 'k') {
                    if (board[i][j]->getHasMoved()) continue;
                    if (!board[i][j + 1] && !board[i][j + 2] && board[i][j + 3] && std::tolower(board[i][j + 3]->toChar()) == 'r' && !board[i][j + 3]->getHasMoved()) {
                        if (!checkThreatened(Position(j, i))[otherSide] && !checkThreatened(Position(j + 1, i))[otherSide] && !checkThreatened(Position(j + 2, i))[otherSide]) {
                            moves.push_back(Move(Position(j, i), Position(j + 2, i), board[i][j], nullptr, enPassantSquare));
                        }
                    }
                    if (!board[i][j - 1] && !board[i][j - 2] && !board[i][j-3] && board[i][j - 4] && std::tolower(board[i][j - 4]->toChar()) == 'r' && !board[i][j - 4]->getHasMoved()) {
                        if (!checkThreatened(Position(j, i))[otherSide] && !checkThreatened(Position(j - 1, i))[otherSide] && !checkThreatened(Position(j - 2, i))[otherSide]) {
                            moves.push_back(Move(Position(j, i), Position(j - 2, i), board[i][j], nullptr, enPassantSquare));
                        }
                    }
                }
            }
        }
    }
    std::vector<Move> legalMoves;
    legalMoves.reserve(moves.size());
    for (auto move : moves) {
        testMove(move);
        if (validateBoard(side)) {
            legalMoves.push_back(move);
        }
        undoMove();
    }
    return legalMoves;
}

bool Board::placePiece(Position pos, char piece) {
    if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE) return false;
    if (board[pos.y][pos.x]) return false;
    Color color = std::isupper(piece) ? Color::White : Color::Black;
    switch (std::tolower(piece)) {
    case 'a':
        allPieces.push_back(std::make_unique<Angel>(color));
        break;
    case 'b':
        allPieces.push_back(std::make_unique<Bishop>(color));
        break;
    case 'c':
        allPieces.push_back(std::make_unique<Cougar>(color));
        break;
    case 'd':
        allPieces.push_back(std::make_unique<Demon>(color));
        break;
    case 'e':
        allPieces.push_back(std::make_unique<RossEvans>(color));
        break;
    case 'f':
        allPieces.push_back(std::make_unique<Fencer>(color));
        break;
    case 'g':
        allPieces.push_back(std::make_unique<Ghost>(color));
        break;
    case 'h':
        allPieces.push_back(std::make_unique<Hippo>(color));
        break;
    case 'i':
        allPieces.push_back(std::make_unique<Imp>(color));
        break;
    case 'j':
        allPieces.push_back(std::make_unique<Juggernaut>(color));
        break;
    case 'k':
        allPieces.push_back(std::make_unique<King>(color));
        break;
    case 'l':
        allPieces.push_back(std::make_unique<Legionary>(color));
        break;
    case 'm':
        allPieces.push_back(std::make_unique<Moat>(color));
        break;
    case 'n':
        allPieces.push_back(std::make_unique<Knight>(color));
        break;
    case 'o':
        allPieces.push_back(std::make_unique<Orc>(color));
        break;
    case 'p':
        allPieces.push_back(std::make_unique<Pawn>(color));
        break;
    case 'q':
        allPieces.push_back(std::make_unique<Queen>(color));
        break;
    case 'r':
        allPieces.push_back(std::make_unique<Rook>(color));
        break;
    case 's':
        allPieces.push_back(std::make_unique<Shinobi>(color));
        break;
    case 't':
        allPieces.push_back(std::make_unique<Thief>(color));
        break;
    case 'u':
        allPieces.push_back(std::make_unique<Unicorn>(color));
        break;
    case 'v':
        allPieces.push_back(std::make_unique<Valkyrie>(color));
        break;
    case 'w':
        allPieces.push_back(std::make_unique<Warrior>(color));
        break;
    case 'x':
        allPieces.push_back(std::make_unique<Axeman>(color));
        break;
    case 'y':
        allPieces.push_back(std::make_unique<Wyvern>(color));
        break;
    case 'z':
        allPieces.push_back(std::make_unique<Zebra>(color));
        break;
    default:
        return false;
    }
    board[pos.y][pos.x] = allPieces.back().get();
    return true;
}

char Board::getState(Position pos) const {
    if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE) return ' ';
    if (board[pos.y][pos.x]) return board[pos.y][pos.x]->toChar();
    return ((pos.x + pos.y) % 2 ? ' ' : '_');
}