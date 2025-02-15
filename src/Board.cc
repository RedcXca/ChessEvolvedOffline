#include "Board.h"
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "ChessException.h"
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

Board::Board(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    for (int y = SIZE - 1; y >= 0 && std::getline(file, line); --y)
        for (int x = 0; x < std::min(SIZE, (int) line.size()); ++x)
            if (line[x] != ' ')
                placePiece(Position(x, y), line[x]);
}

inline int signum(int x) { return (x > 0) - (x < 0); }

bool Board::validateBoard(Color side) { return !checkThreatened(kingPositions.at(side))[getNextColor(side)]; }

void Board::undoMove() {
    testUndo();
    legalMoveHistory.pop_back();
}
void Board::testUndo() {
    if (!history.size()) throw ChessException("No move to undo");
    Move lastMove = std::move(history.back());
    history.pop_back();
    board[lastMove.from.y][lastMove.from.x] = lastMove.originalPiece; // reset original piece
    if (lastMove.originalPiece->toChar() != board[lastMove.to.y][lastMove.to.x]->toChar()) {
        allPieces.pop_back(); // this means it's a promotion
    }
    if (lastMove.enPassantPos == lastMove.to && isPiece(lastMove.originalPiece, 'p')) {
        board[lastMove.to.y][lastMove.to.x] = nullptr;
        lastMove.to.y += lastMove.originalPiece->getColor() == Color::White ? -1 : 1;
    } // adjust position of captured piece for en passant
    board[lastMove.to.y][lastMove.to.x] = lastMove.capturedPiece;
    if (isPiece(lastMove.originalPiece, 'k')) {
        kingPositions.insert_or_assign(lastMove.originalPiece->getColor(), lastMove.from);
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
    currColor = getNextColor(currColor);
    enPassantSquare = lastMove.enPassantPos;
}

bool Board::checkBlocked(Position pos, int deltaX, int deltaY, bool attackable, Color otherSide) {
    for (int i = 1; i < std::max(std::abs(deltaX), std::abs(deltaY)); ++i) // go up to one before the target square
        if (board[pos.y + i * signum(deltaY)][pos.x + i * signum(deltaX)]) return true;
    if (board[pos.y + deltaY][pos.x + deltaX]) return !attackable || board[pos.y + deltaY][pos.x + deltaX]->getColor() != otherSide; // there is a piece there to be attacked
    return false;
}

// template function for threat checks
template<typename Func>
void Board::checkThreatenedImpl(Position pos, Func func) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j]) {
                for (auto move : board[i][j]->getPossibleMoves()) {
                    if (i + move.deltaY == pos.y && j + move.deltaX == pos.x) {
                        if (move.type == MoveType::MoveOnly || move.type == MoveType::Teleport) continue;
                        if (move.type == MoveType::AttackOnly || move.type == MoveType::MoveOrAttack) {
                            if (checkBlocked({j, i}, move.deltaX, move.deltaY, true, getNextColor(board[i][j]->getColor()))) continue;
                        }
                        func(board[i][j]);
                    }
                }
            }
        }
    }
}

// Returns the number of pieces threatening the given position for each color
std::map<Color, int> Board::checkThreatened(Position pos) {
    std::map<Color, int> threatened;
    checkThreatenedImpl(pos, [&](Piece* piece) {
        threatened[piece->getColor()]++;
    });
    return threatened;
}

// Returns a vector of the pieces threatening the given position for each color
std::map<Color, std::vector<Piece*>> Board::checkThreatenedPieces(Position pos) {
    std::map<Color, std::vector<Piece*>> threatened;
    checkThreatenedImpl(pos, [&](Piece* piece) {
        threatened[piece->getColor()].push_back(piece);
    });
    return threatened;
}

void Board::makeMove(Move move) {
    testMove(move);
    generateLegalMoves();
}

// assumes move is legal (ignoring checks)
void Board::testMove(Move move) {
    history.push_back(move);
    board[move.to.y][move.to.x] = move.originalPiece;
    board[move.from.y][move.from.x] = nullptr;
    if (move.enPassantPos == move.to && isPiece(move.originalPiece, 'p')) {
        board[move.to.y + (move.originalPiece->getColor() == Color::White ? -1 : 1)][move.to.x] = nullptr;
    }
    if (isPiece(move.originalPiece, 'k')) {
        kingPositions.insert_or_assign(move.originalPiece->getColor(), move.to);
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
    if (isPiece(move.originalPiece, 'p') && std::abs(move.to.y - move.from.y) == 2) {
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
    currColor = getNextColor(currColor);
}

const std::vector<Move>& Board::generateLegalMoves() {
    Color otherSide = getNextColor(currColor);
    std::vector<Move> moves;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] && board[i][j]->getColor() == currColor) {
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
                            } else if (isPiece(board[i][j], 'p')) {
                                if (enPassantSquare == Position(x, y)) {
                                    moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y + (currColor == Color::White ? -1 : 1)][x], enPassantSquare));
                                }
                            }
                        } else if (move.type == MoveType::UnblockableMoveOrAttack) {
                            if (!board[y][x] || board[y][x]->getColor() == otherSide) moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y][x], enPassantSquare));
                        } else if (move.type == MoveType::Teleport) {
                            if (!board[y][x]) moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], nullptr, enPassantSquare));
                        } else if (move.type == MoveType::UnblockableAttackOnly) {
                            if (board[y][x] && board[y][x]->getColor() == otherSide) {
                                moves.push_back(Move(Position(j, i), Position(x, y), board[i][j], board[y][x], enPassantSquare));
                            }
                        }
                    }
                }
                if (isPiece(board[i][j], 'k')) {
                    if (j != 4 || board[i][j]->getHasMoved()) continue;
                    if (!board[i][j + 1] && !board[i][j + 2] && board[i][j + 3] && std::tolower(board[i][j + 3]->toChar()) == 'r' && !board[i][j + 3]->getHasMoved()) {
                        if (!checkThreatened(Position(j, i))[otherSide] && !checkThreatened(Position(j + 1, i))[otherSide] && !checkThreatened(Position(j + 2, i))[otherSide]) {
                            moves.push_back(Move(Position(j, i), Position(j + 2, i), board[i][j], nullptr, enPassantSquare));
                        }
                    }
                    if (!board[i][j - 1] && !board[i][j - 2] && !board[i][j - 3] && board[i][j - 4] && std::tolower(board[i][j - 4]->toChar()) == 'r' && !board[i][j - 4]->getHasMoved()) {
                        if (!checkThreatened(Position(j, i))[otherSide] && !checkThreatened(Position(j - 1, i))[otherSide] && !checkThreatened(Position(j - 2, i))[otherSide]) {
                            moves.push_back(Move(Position(j, i), Position(j - 2, i), board[i][j], nullptr, enPassantSquare));
                        }
                    }
                }
            }
        }
    }
    std::vector<Move> newLegalMoves;
    newLegalMoves.reserve(moves.size());
    for (auto move : moves) {
        std::vector<Move> currMoves;
        if (isPiece(move.originalPiece, 'p') && move.to.y == (move.originalPiece->getColor() == Color::White ? 7 : 0)) {
            for (char promotion : PROMOTION_CHOICES) {
                move.promotionPiece = promotion;
                currMoves.push_back(move);
            }
        } else
            currMoves.push_back(move);
        for (auto currMove : currMoves) {
            testMove(currMove);
            if (validateBoard(getNextColor(currColor))) {
                if (!validateBoard(currColor)) currMove.check = true;
                newLegalMoves.push_back(currMove);
            }
            testUndo();
        }
    }
    legalMoveHistory.push_back(newLegalMoves);
    return legalMoveHistory.back();
}

const std::vector<Move>& Board::getLegalMoves() {
    return legalMoveHistory.back();
}

bool Board::placePiece(Position pos, char piece) {
    if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE) return false;
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
        kingPositions.insert_or_assign(color, pos); // initialize king pos
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
    if (board[pos.y][pos.x])
        std::erase_if(allPieces, [&](const auto& p) {
            return p.get() == board[pos.y][pos.x];
        });
    board[pos.y][pos.x] = allPieces.back().get();
    return true;
}

Board::SquareState Board::getState(Position pos) const {
    if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE) return {' ', false};
    Board::SquareState state;
    state.piece = board[pos.y][pos.x] ? board[pos.y][pos.x]->toChar() : ' ';
    state.highlighted = false;
    if (selected != Position(-1, -1) && board[selected.y][selected.x]) {
        for (auto move : legalMoveHistory.back()) {
            if (move.from == selected && move.to == pos) {
                state.highlighted = true;
                break;
            }
        }
    }
    return state;
}

bool Board::removePiece(Position pos) {
    if (pos.x < 0 || pos.x >= SIZE || pos.y < 0 || pos.y >= SIZE || !board[pos.y][pos.x]) return false;
    auto it = std::find_if(allPieces.begin(), allPieces.end(), [&](const auto& p) { return p.get() == board[pos.y][pos.x]; });
    if (it != allPieces.end()) allPieces.erase(it);
    board[pos.y][pos.x] = nullptr;
    return true;
}

Color Board::getSide() const {
    return currColor;
}

void Board::setColor(Color c) {
    currColor = c;
}

Position Board::getSelected() {
    return selected;
}
void Board::setSelected(Position p) {
    selected = p;
}
Piece* Board::getPiece(Position p) {
    return board[p.y][p.x];
}

const std::vector<Move>& Board::getMoveHistory() const {
    return history;
}
