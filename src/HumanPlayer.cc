#include "HumanPlayer.h"
#include <string>
#include <iostream>
#include <sstream>
#include "ChessException.h"
MoveInput HumanPlayer::getNextMove(Board& board) {
    std::string line, start, end;
    getline(std::cin, line);
    std::istringstream ss{line};
    if (!(ss >> start >> end)) throw ChessException{"Must enter two positions!"};
    char p{};
    ss >> p;
    return MoveInput{Position{start}, Position{end}, p};
}
