#ifndef THIEF_H
#define THIEF_H
#include "piece.h"

// Watch your back with this guy, he can show up out of nowhere and stab you in the back

class Thief : public Piece {
public:
    char toChar() override;
    int getValue() override;
    std::vector<PartialMove> getPossibleMoves() override;
};
#endif