#include "unicorn.h"

char Unicorn::toChar() {
    return color == Color::White ? 'U' : 'u';
}
int Unicorn::getValue() {
    return 7;
}
std::vector<PartialMove> Unicorn::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
    pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
    return moves;
}
