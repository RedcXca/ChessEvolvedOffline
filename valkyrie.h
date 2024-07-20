#ifndef VALKYRIE_H
#define VALKYRIE_H
#include "piece.h"

// Tricky to maneuver, devastating when maneuvered correctly

class Valkyrie : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'V' : 'v';
    }
    int getValue() override {
        return 4;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushValkyrieMoves(moves, MoveType::UnblockableMoveOrAttack);
        return moves;
    }
};
#endif