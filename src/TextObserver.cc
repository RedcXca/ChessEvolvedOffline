#include "TextObserver.h"
#include "Game.h"
#include <iostream>

void TextObserver::update() {
    for (int i = Board::SIZE - 1; i >= 0; i--) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < Board::SIZE; j++) {
            Board::SquareState state = game->getState(Position(j, i));
            char piece = state.piece;
            bool highlighted = state.highlighted;
            if (piece == ' ') {
                piece = highlighted ? '@' : ((j + i) % 2 == 0) ? ' ' : '_';
                std::cout << piece << ' ';
            } else if (highlighted)
                std::cout << "\033[31m" << piece << "\033[0m ";
            else
                std::cout << piece << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "\n   a b c d e f g h" << std::endl;
}
