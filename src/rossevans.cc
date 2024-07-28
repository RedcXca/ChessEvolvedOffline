#include "rossevans.h"

char RossEvans::toChar() {
    return color == Color::White ? 'E' : 'e';
}

int RossEvans::getValue() {
    return 12;
}

std::vector<PartialMove> RossEvans::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushRookMoves(moves, 7, MoveType::MoveOrAttack);
    pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
    pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
    return moves;
}
