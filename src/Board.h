#ifndef BOARD_H
#define BOARD_H
#include "move.h"
#include <vector>
#include <array>
#include <map>
#include "color.h"
#include "position.h"
#include <memory>
#include <string>

struct Board {
    friend class Game;
    static inline constexpr int SIZE = 8;
    Board(const std::string& fileName = "initialState.txt");
    bool validateBoard(Color side);
    std::map<Color, int> checkThreatened(Position);
    const std::vector<Move>& generateLegalMoves();
    const std::vector<Move>& getLegalMoves();
    void makeMove(Move);
    void undoMove();
    char getState(Position) const;
    Color getSide() const;

private:
    std::vector<Move> history;
    std::vector<Move> legalMoves;
    std::array<std::array<Piece*, SIZE>, SIZE> board{};
    std::map<Color, Position> kingPositions;
    std::vector<std::unique_ptr<Piece>> allPieces;
    Position enPassantSquare{-1, -1};
    Color currColor{};
    bool checkBlocked(Position, int deltaX, int deltaY, bool attackable = false, Color otherSide = Color::White);
    bool placePiece(Position, char);
    void removePiece(Position);
    void setColor(Color);
};
#endif
