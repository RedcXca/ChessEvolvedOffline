#ifndef FENCER_H
#define FENCER_H
#include "piece.h"

// Fencer has the ability to teleport deep into enemy lines, posing dangerous threats

class Fencer : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'F' : 'f';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushBishopMoves(moves, 4, MoveType::Teleport);
        pushRookMoves(moves, 2, MoveType::MoveOrAttack);
        return moves;
    }
};
#endif