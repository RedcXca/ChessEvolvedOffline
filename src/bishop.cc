#include "bishop.h"

char Bishop::toChar() {
    return color == Color::White ? 'B' : 'b';
}
int Bishop::getValue() {
    return 3;
}
std::vector<PartialMove> Bishop::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushBishopMoves(moves, 7, MoveType::MoveOrAttack);
    return moves;
}
