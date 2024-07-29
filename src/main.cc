#include <iostream>
#include <string>
#include "Game.h"
#include "Observer.h"
#include "TextObserver.h"
#include "GraphicObserver.h"
#include "Subject.h"
#include "ChessException.h"

int main() {
    Game game;
    TextObserver textObserver(&game);
    // GraphicsObserver graphicsObserver(&game);
    // game.attach(&graphicsObserver);

    // game.notifyObservers();

    for (std::string command; std::cin >> command;) {
        try {
            if (std::string player1, player2; command == "game") {
                std::cin >> player1 >> player2;
                game.play({{Color::White, player1}, {Color::Black, player2}});
            } else if (command == "setup")
                game.setup();
            else
                std::cerr << "Invalid command!\n";
        } catch (const ChessException& ce) {
            std::cerr << ce.what() << '\n';
        }
    }
    game.reportResults();
}
