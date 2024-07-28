#include "valkyrie.h"

char Valkyrie::toChar() {
    return color == Color::White ? 'V' : 'v';
}
int Valkyrie::getValue() {
    return 4;
}

std::vector<PartialMove> Valkyrie::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushValkyrieMoves(moves, MoveType::UnblockableMoveOrAttack);
    return moves;
}
