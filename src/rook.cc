#include "rook.h"

char Rook::toChar() {
    return color == Color::White ? 'R' : 'r';
}
int Rook::getValue() {
    return 5;
}
std::vector<PartialMove> Rook::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushRookMoves(moves, 7, MoveType::MoveOrAttack);
    return moves;
}
