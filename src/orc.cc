#include "orc.h"

char Orc::toChar() {
    return color == Color::White ? 'O' : 'o';
}
int Orc::getValue() {
    return 3;
}
std::vector<PartialMove> Orc::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKingMoves(moves, MoveType::MoveOrAttack);
    return moves;
}
