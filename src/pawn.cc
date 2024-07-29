#include "pawn.h"

char Pawn::toChar() {
    return color == Color::White ? 'P' : 'p';
}
int Pawn::getValue() {
    return 1;
}
std::vector<PartialMove> Pawn::getPossibleMoves() {
    std::vector<PartialMove> moves;
    int direction = color == Color::White ? 1 : -1;
    moves.push_back({0, direction, MoveType::MoveOnly});
    if (!hasMoved) moves.push_back({0, 2 * direction, MoveType::MoveOnly});
    moves.push_back({1, direction, MoveType::AttackOnly});
    moves.push_back({-1, direction, MoveType::AttackOnly});
    return moves;
}
