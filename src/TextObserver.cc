#include "TextObserver.h"
#include "Game.h"
#include <iostream>

TextObserver::TextObserver(Subject* s)
    : Observer(s) {}

void TextObserver::update() {
    auto game = dynamic_cast<Game*>(subject);
    if (!game) return;

    for (int i = 7; i >= 0; --i) {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < 8; ++j) {
            std::cout << game->getState(Position(j, i)) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}
