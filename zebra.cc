#include "zebra.h"

char Zebra::toChar() {
    return color == Color::White ? 'Z' : 'z';
}
int Zebra::getValue() {
    return 4;
}
std::vector<PartialMove> Zebra::getPossibleMoves() {
    std::vector<PartialMove> moves;
    pushZebraMoves(moves, MoveType::UnblockableMoveOrAttack);
    return moves;
}