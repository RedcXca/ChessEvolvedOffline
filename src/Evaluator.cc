#include "Evaluator.h"
#include "UnrecoverableChessException.h"

Evaluator::Evaluator(char pieceType): pieceType{pieceType}{
    std::ifstream file(std::string{"./evaluations/"} + pieceType + ".txt");
    if (!file.is_open())
        throw UnrecoverableChessException{std::string{"Could not open file evaluations/"} + pieceType + ".txt"};
    for (int i = 0; i < Board::SIZE; ++i)
        for (int j = 0; j < Board::SIZE; ++j)
            if (!(file >> evals[i][j]))
                throw UnrecoverableChessException{"Error reading file"};
}

int Evaluator::getEval(Position p, Color c){
    return evals[c == Color::White ? Board::SIZE - p.y - 1 : p.y][p.x];
}
