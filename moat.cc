#include "moat.h"

char Moat::toChar() {
    return color == Color::White ? 'M' : 'm';
}
int Moat::getValue() {
    return 3;
}
std::vector<PartialMove> Moat::getPossibleMoves() {
    std::vector<PartialMove> moves;
    for (int i = -7; i <= 7; i++) {
        moves.push_back({i, 0, MoveType::UnblockableAttackOnly});
    }
    if (!hasMoved) {
        moves.push_back({0, 1, MoveType::MoveOnly});
        moves.push_back({1, 1, MoveType::MoveOnly});
        moves.push_back({-1, 1, MoveType::MoveOnly});
    }
    return moves;
}