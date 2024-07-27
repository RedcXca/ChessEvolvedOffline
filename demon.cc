#include "demon.h"
char Demon::toChar() {
    return color == Color::White ? 'D' : 'd';
}
int Demon::getValue() {
    return 4;
}
std::vector<PartialMove> Demon::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKnightMoves(moves, MoveType::Teleport);
    pushRookMoves(moves, 4, MoveType::MoveOrAttack);
}