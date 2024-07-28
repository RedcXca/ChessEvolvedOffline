#include "cougar.h"

char Cougar::toChar() {
    return color == Color::White ? 'C' : 'c';
}
int Cougar::getValue() {
    return 3;
}
std::vector<PartialMove> Cougar::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushZebraMoves(moves, MoveType::Teleport);
    pushKnightMoves(moves, MoveType::Teleport);
    pushBishopMoves(moves, 2, MoveType::UnblockableAttackOnly, 2);
    return moves;
}