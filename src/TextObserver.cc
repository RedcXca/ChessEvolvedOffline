#include "TextObserver.h"
#include "Game.h"
#include <iostream>

TextObserver::TextObserver(Subject* s)
    : Observer(s) {}

void TextObserver::update() {
    auto game = dynamic_cast<Game*>(subject);
    if (!game) return;

    for (int i = Board::SIZE - 1; i >= 0; i--) {
        std::cout << i << "  ";
        for (int j = 0; j < Board::SIZE; j++) {
            std::cout << game->getState(Position(j, i)) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "\n  a b c d e f g h" << std::endl;
}
