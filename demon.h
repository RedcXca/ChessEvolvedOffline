#ifndef DEMON_H
#define DEMON_H
#include "piece.h"

// Demon trades off some of the higher range of a rook for knight teleports

class Demon : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'D' : 'd';
    }
    int getValue() override {
        return 4;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKnightMoves(moves, MoveType::Teleport);
        pushRookMoves(moves, 4, MoveType::MoveOrAttack);
    }
};
#endif