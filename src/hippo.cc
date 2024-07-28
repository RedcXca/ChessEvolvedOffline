#include "hippo.h"

char Hippo::toChar() {
    return color == Color::White ? 'H' : 'h';
}
int Hippo::getValue() {
    return 7;
}
std::vector<PartialMove> Hippo::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKnightMoves(moves, MoveType::UnblockableAttackOnly);
    pushValkyrieMoves(moves, MoveType::UnblockableAttackOnly);
    pushRookMoves(moves, 1, MoveType::MoveOrAttack);
    pushBishopMoves(moves, 1, MoveType::AttackOnly);
    pushRookMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
    return moves;
}
