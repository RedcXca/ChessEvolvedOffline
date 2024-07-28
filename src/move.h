#ifndef MOVE_H
#define MOVE_H
#include "position.h"
#include "piece.h"
struct Move {
    Position from, to;
    Piece* originalPiece;
    Piece* capturedPiece;
    char promotionPiece;
    bool enPassant;
    std::string toString();
};
#endif