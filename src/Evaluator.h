#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "Piece.h"
#include <fstream>
#include "Board.h"
#include "position.h"
#include "color.h"
#include <array>

class Evaluator {
    std::array<std::array<int, Board::SIZE>, Board::SIZE> evals;
    char pieceType;

public:
    explicit Evaluator(char);
    int getEval(Position, Color);
};
#endif
