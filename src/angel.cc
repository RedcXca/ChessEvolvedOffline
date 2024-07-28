#include "angel.h"

char Angel::toChar() {
    return color == Color::White ? 'A' : 'a';
}
int Angel::getValue() {
    return 7;
}
std::vector<PartialMove> Angel::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushValkyrieMoves(moves, MoveType::UnblockableMoveOrAttack);
    pushRookMoves(moves, 2, MoveType::MoveOrAttack);
    return moves;
}
