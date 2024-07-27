#include "thief.h"

char Thief::toChar() {
    return color == Color::White ? 'T' : 't';
}
int Thief::getValue() {
    return 3;
}

std::vector<PartialMove> Thief::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKingMoves(moves, MoveType::AttackOnly);
    pushRookMoves(moves, 3, MoveType::Teleport, 3);
    pushZebraMoves(moves, MoveType::Teleport);
    moves.push_back({0, -2, MoveType::UnblockableAttackOnly});
    return moves;
}
