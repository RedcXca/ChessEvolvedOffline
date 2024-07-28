#include "shinobi.h"

char Shinobi::toChar() {
    return color == Color::White ? 'S' : 's';
}
int Shinobi::getValue() {
    return 5;
}

std::vector<PartialMove> Shinobi::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushKingMoves(moves, MoveType::MoveOrAttack);
    pushBishopMoves(moves, 2, MoveType::UnblockableMoveOrAttack, 2);
    pushRookMoves(moves, 3, MoveType::UnblockableMoveOrAttack, 3);
    return moves;
}
