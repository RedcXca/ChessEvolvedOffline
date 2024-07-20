#ifndef THIEF_H
#define THIEF_H
#include "piece.h"

// Watch your back with this guy, he can show up out of nowhere and stab you in the back

class Thief : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'T' : 't';
    }
    int getValue() override {
        return 3;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushKingMoves(moves, MoveType::AttackOnly);
        pushRookMoves(moves, 3, MoveType::Teleport, 3);
        pushZebraMoves(moves, MoveType::Teleport);
        moves.push_back({0, -2, MoveType::UnblockableAttackOnly});
        return moves;
    }
};
#endif