#ifndef PIECE_H
#define PIECE_H
#include "color.h"
#include "partialmove.h"
#include <vector>
class Piece {
protected:
    Color color;
    bool hasMoved = false;
    void pushRookMoves(std::vector<PartialMove>& moves, int range, MoveType type, int innerRange = 1);
    void pushBishopMoves(std::vector<PartialMove>& moves, int range, MoveType type, int innerRange = 1);
    void pushKingMoves(std::vector<PartialMove>& moves, MoveType type);
    void pushKnightMoves(std::vector<PartialMove>& moves, MoveType type);
    void pushValkyrieMoves(std::vector<PartialMove>& moves, MoveType type);
    void pushZebraMoves(std::vector<PartialMove>& moves, MoveType type);

public:
    bool getHasMoved() { return hasMoved; }
    void setHasMoved(bool hasMoved) { this->hasMoved = hasMoved; }
    virtual int getValue() = 0;
    Color getColor() { return color; }
    virtual std::vector<PartialMove> getPossibleMoves() = 0;
    virtual char toChar() = 0;
    Piece(Color color) : color(color) {}
};
#endif
