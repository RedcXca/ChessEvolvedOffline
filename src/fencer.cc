#include "fencer.h"

char Fencer::toChar() {
    return color == Color::White ? 'F' : 'f';
}
int Fencer::getValue() {
    return 4;
}
std::vector<PartialMove> Fencer::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushBishopMoves(moves, 4, MoveType::Teleport);
    pushRookMoves(moves, 2, MoveType::MoveOrAttack);
    return moves;
}