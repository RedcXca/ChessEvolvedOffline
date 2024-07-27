#include "move.h"
#include <vector>
#include <array>
#include <map>
#include "color.h"
#include "position.h"

class Board {
    std::vector<Move> history;
    std::array<std::array<Piece*, 8>, 8> board;
    std::map<Color, Position> kingPositions;
    public:
    void undoMove();
    std::map<Color, int> checkThreatened(Position);
    bool validateBoard(Color side);
    void makeMove(Move);
    std::vector<Move> generateLegalMoves(Color side);
};