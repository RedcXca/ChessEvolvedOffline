#ifndef ZEBRA_H
#define ZEBRA_H
#include "piece.h"

// Zebra moves are immensely tricky to predict, but in the right hands their reach is devastating

class Zebra : public Piece {
public:
    char toChar() override {
        return color == Color::White ? 'Z' : 'z';
    }
    int getValue() override {
        return 4;
    }
    std::vector<PartialMove> getPossibleMoves() override {
        std::vector<PartialMove> moves;
        pushZebraMoves(moves, MoveType::UnblockableMoveOrAttack);
        return moves;
    }
};
#endif