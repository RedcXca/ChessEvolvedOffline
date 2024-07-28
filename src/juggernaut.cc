#include "juggernaut.h"

char Juggernaut::toChar() {
    return color == Color::White ? 'J' : 'j';
}
int Juggernaut::getValue() {
    return 7;
}
std::vector<PartialMove> Juggernaut::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKnightMoves(moves, MoveType::UnblockableMoveOrAttack);
    pushKingMoves(moves, MoveType::MoveOrAttack);
    pushRookMoves(moves, 2, MoveType::MoveOrAttack, 2);
    return moves;
}

