#include "queen.h"

char Queen::toChar() {
    return color == Color::White ? 'Q' : 'q';
}
int Queen::getValue() {
    return 9;
}
std::vector<PartialMove> Queen::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
    pushRookMoves(moves, 7, MoveType::MoveOrAttack);
    return moves;
}
