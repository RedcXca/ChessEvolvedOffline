#ifndef COUGAR_H
#define COUGAR_H
#include "piece.h"

// Unpredictable piece with few threat squares, but very tricky mobility and ability to infiltrate

class Cougar : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'C' : 'c';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushZebraMoves(moves, MoveType::Teleport);
        pushKnightMoves(moves, MoveType::Teleport);
        pushBishopMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
        return moves;
    }
};
#endif