#ifndef AXEMAN_H
#define AXEMAN_H
#include "piece.h"

// Axeman is a more defensive, shorter ranged bishop that can swap color complexes

class Axeman : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'X' : 'x';
    }
    int getValue() override {
        return 2;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushBishopMoves(moves, 2, MoveType::MoveOrAttack);
        pushRookMoves(moves, 1, MoveType::MoveOnly);
        return moves;
    }
};
#endif