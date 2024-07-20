#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

// Classic chess knight

class Knight : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'N' : 'n';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
        return moves;
    }
};
#endif