#include "legionary.h"

char Legionary::toChar() {
    return color == Color::White ? 'L' : 'l';
}
int Legionary::getValue() {
    return 5;
}
std::vector<PartialMove> Legionary::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKingMoves(moves, MoveType::MoveOrAttack);
    pushBishopMoves(moves, 3, MoveType::AttackOnly, 2);
    pushRookMoves(moves, 2, MoveType::AttackOnly, 2);
    return moves;
}
