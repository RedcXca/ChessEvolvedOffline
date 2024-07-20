#ifndef ROSS_EVANS_H
#define ROSS_EVANS_H
#include "piece.h"

// The man, the myth, the legend, the strongest piece in the game

class RossEvans : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'E' : 'e';
    }
    int getValue() override {
        return 12;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushRookMoves(moves, 7, MoveType::MoveOrAttack);
        pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
        pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
        return moves;
    }
};
#endif;