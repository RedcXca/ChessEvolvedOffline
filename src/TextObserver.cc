#include "TextObserver.h"
#include "Game.h"
#include <iostream>

void TextObserver::update() {
    if (!game) return;

    for (int i = Board::SIZE - 1; i >= 0; i--) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < Board::SIZE; j++) {
            std::cout << game->getState(Position(j, i)) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "\n   a b c d e f g h" << std::endl;
}
