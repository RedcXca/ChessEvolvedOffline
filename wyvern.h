#ifndef WYVERN_H
#define WYVERN_H
#include "piece.h"

// Wyvern is agile and eternally tricky with its teleports

class Wyvern : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'Y' : 'y';
    }
    int getValue() override {
        return 2;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushRookMoves(moves, 1, MoveType::MoveOrAttack);
        pushRookMoves(moves, 2, MoveType::AttackOnly, 2);
        pushBishopMoves(moves, 2, MoveType::Teleport), 2;
        return moves;
    }
};
#endif