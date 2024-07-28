#include "move.h"
#include <vector>
#include <array>
#include <map>
#include "color.h"
#include "position.h"

struct Board {
    static inline constexpr int SIZE = 8;
    void undoMove();
    std::map<Color, int> checkThreatened(Position);
    bool validateBoard(Color side);
    void makeMove(Move);
    std::vector<Move> generateLegalMoves(Color side);

private:
    std::vector<Move> history;
    std::array<std::array<Piece*, SIZE>, SIZE> board;
    std::map<Color, Position> kingPositions;
};
