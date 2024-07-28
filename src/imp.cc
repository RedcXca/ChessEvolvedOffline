#include "imp.h"

char Imp::toChar() {
    return color == Color::White ? 'I' : 'i';
}
int Imp::getValue() {
    return 2;
}
std::vector<PartialMove> Imp::getPossibleMoves() {
    std::vector<PartialMove> moves;
    moves.push_back({0, 1, MoveType::MoveOrAttack});
    moves.push_back({0, -1, MoveType::MoveOrAttack});
    moves.push_back({0, 2, MoveType::UnblockableMoveOrAttack});
    moves.push_back({0, -2, MoveType::UnblockableMoveOrAttack});
    moves.push_back({1, -2, MoveType::Teleport});
    moves.push_back({-1, -2, MoveType::Teleport});
    moves.push_back({1, 2, MoveType::Teleport});
    moves.push_back({-1, 2, MoveType::Teleport});
    return moves;
}
