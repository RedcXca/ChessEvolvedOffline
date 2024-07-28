#include "wyvern.h"

char Wyvern::toChar() {
    return color == Color::White ? 'Y' : 'y';
}
int Wyvern::getValue() {
    return 2;
}

std::vector<PartialMove> Wyvern::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushRookMoves(moves, 1, MoveType::MoveOrAttack);
    pushRookMoves(moves, 2, MoveType::AttackOnly, 2);
    pushBishopMoves(moves, 2, MoveType::Teleport), 2;
    return moves;
}
