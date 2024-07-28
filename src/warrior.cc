#include "warrior.h"

char Warrior::toChar() {
    return color == Color::White ? 'W' : 'w';
}
int Warrior::getValue() {
    return 4;
}

std::vector<PartialMove> Warrior::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushRookMoves(moves, 2, MoveType::MoveOrAttack);
    pushBishopMoves(moves, 2, MoveType::MoveOrAttack);
    return moves;
}
