#include "Evaluator.h"
Evaluator::Evaluator(char pieceType): pieceType{pieceType}{
    std::ifstream file("./evaluations/" + std::string(1, pieceType) + ".txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file evaluations/" + std::string(1, pieceType) + ".txt");
    }
    for (int i = 0; i < Board::SIZE; ++i) {
        for (int j = 0; j < Board::SIZE; ++j) {
            if (!(file >> evals[i][j])) {
                throw std::runtime_error("Error reading file");
            }
        }
    }
}

int Evaluator::getEval(Position p, Color c){
    return evals[c == Color::White ? Board::SIZE - p.y - 1 : p.y][p.x];
}
