#include "ghost.h"

char Ghost::toChar() {
    return color == Color::White ? 'G' : 'g';
}
int Ghost::getValue() {
    return 3;
}
std::vector<PartialMove> Ghost::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushRookMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
    pushBishopMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
    pushRookMoves(moves, 4, MoveType::Teleport, 4);
    pushRookMoves(moves, 6, MoveType::Teleport, 6);
    if (!hasMoved) pushKnightMoves(moves, MoveType::Teleport);
    return moves;
}
