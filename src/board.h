#include "move.h"
#include <vector>
#include <array>
#include <map>
#include "color.h"
#include "position.h"
#include <memory>
#include <string>

struct Board {
    static inline constexpr int SIZE = 8;
    void undoMove();
    std::map<Color, int> checkThreatened(Position);
    bool validateBoard(Color side);
    void makeMove(Move);
    std::vector<Move> generateLegalMoves(Color side);
    bool placePiece(Position, char);
    void removePiece(Position);
    char getState(Position) const;
    void setColor(Color);

private:
    std::vector<Move> history;
    std::array<std::array<Piece*, SIZE>, SIZE> board{};
    std::map<Color, Position> kingPositions;
    std::vector<std::unique_ptr<Piece>> allPieces;
    Position enPassantSquare{-1, -1};
    Color currColor{};
    bool checkBlocked(Position, int deltaX, int deltaY, bool attackable = false, Color otherSide = Color::White);
    void testMove(Move move);
};
