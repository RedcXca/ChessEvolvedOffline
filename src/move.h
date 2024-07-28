#ifndef MOVE_H
#define MOVE_H
#include "position.h"
#include "piece.h"
struct Move {
    Position from, to;
    Piece* originalPiece;
    Piece* capturedPiece;
    bool firstMove;
    Position enPassantPos = Position(-1, -1);
    char promotionPiece {};
    std::string toString();
    Move(Position from, Position to, Piece* originalPiece, Piece* capturedPiece, Position enPassantPos, char promotionPiece = 0) : from(from), to(to), originalPiece(originalPiece), capturedPiece(capturedPiece), firstMove(!originalPiece->getHasMoved()), enPassantPos(enPassantPos), promotionPiece(promotionPiece) {}
};
#endif
