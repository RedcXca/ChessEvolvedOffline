#ifndef IMP_H
#define IMP_H

#include "piece.h"

// Imp is dangerous on a single column of attack, but it can be a bit awkward to get on the right one

class Imp : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'I' : 'i';
    }
    int getValue() override {
        return 2;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        moves.push_back({0, 1, MoveType::MoveOrAttack});
        moves.push_back({0, -1, MoveType::MoveOrAttack});
        moves.push_back({0, 2, MoveType::UnblockableMoveOrAttack});
        moves.push_back({0, -2, MoveType::UnblockableMoveOrAttack});
        moves.push_back({1, -2, MoveType::Teleport});
        moves.push_back({-1, -2, MoveType::Teleport});
        moves.push_back({1, 2, MoveType::Teleport});
        moves.push_back({-1, 2, MoveType::Teleport});
        return moves;
    }
};
#endif