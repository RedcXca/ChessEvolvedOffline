#include "axeman.h"

char Axeman::toChar() {
    return color == Color::White ? 'X' : 'x';
}
int Axeman::getValue() {
    return 2;
}
std::vector<PartialMove> Axeman::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushBishopMoves(moves, 2, MoveType::MoveOrAttack);
    pushRookMoves(moves, 1, MoveType::MoveOnly);
    return moves;
}