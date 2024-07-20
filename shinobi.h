#ifndef SHINOBI_H
#define SHINOBI_H
#include "piece.h"

// Shinobi is a very tricky piece that is easy to get checkmated by if you're not careful.

class Shinobi : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'S' : 's';
    }
    int getValue() override {
        return 5;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKingMoves(moves, MoveType::MoveOrAttack);
        pushBishopMoves(moves, 2, MoveType::UnblockableMoveOrAttack, 2);
        pushRookMoves(moves, 3, MoveType::UnblockableMoveOrAttack, 3);
        return moves;
    }
};

#endif