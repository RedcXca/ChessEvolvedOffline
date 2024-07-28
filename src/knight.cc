#include "knight.h"

char Knight::toChar() {
    return color == Color::White ? 'N' : 'n';
}
int Knight::getValue() {
    return 3;
}
std::vector<PartialMove> Knight::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
    return moves;
}
