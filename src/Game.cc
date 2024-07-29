#include "Game.h"
#include <iostream>
#include <string>

Game::Game() {
   // TODO
}

char Game::getState(Position p) const {
    return board.getState(p);
}

const Board& Game::getBoard() const {
    return board;
}

void Game::setup() {
    // TODO
    for (std::string command, piece, square; std::cin >> command && command != "done";) {
        if (command == "+") {
            std::cin >> piece >> square;
            board.placePiece(Position{square}, piece[0]);
        } else if (command == "-") {
            std::cin >> square;
            board.removePiece(Position{square});
        } else if (std::string color; command == "=") {
            std::cin >> color;
            if (color == "white") board.setColor(Color::White);
            else if (color == "black") board.setColor(Color::Black);
            else std::cerr << "Invalid color\n";
        } else std::cerr << "Invalid setup command.\n";
    }
}
