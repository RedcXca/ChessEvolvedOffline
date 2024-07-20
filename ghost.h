#ifndef GHOST_H
#define GHOST_H
#include "piece.h"

// Color-bound and double-bound, the Ghost is tricky to maneuver but can deliver devasting forks

class Ghost : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'G' : 'g';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushRookMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
        pushBishopMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
        pushRookMoves(moves, 4, MoveType::Teleport, 4);
        pushRookMoves(moves, 6, MoveType::Teleport, 6);
        if (!hasMoved) pushKnightMoves(moves, MoveType::Teleport);
        return moves;
    }
};
#endif