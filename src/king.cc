#include "king.h"

char King::toChar() {
    return color == Color::White ? 'K' : 'k';
}
int King::getValue() {
    return 0;
}
std::vector<PartialMove> King::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKingMoves(moves, MoveType::MoveOrAttack);
    return moves;
}
