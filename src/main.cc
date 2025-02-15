#include <iostream>
#include <string>
#include "Game.h"
#include "Observer.h"
#include "TextObserver.h"
#include "GraphicsObserver.h"
#include "Subject.h"
#include "ChessException.h"
#include "UnrecoverableChessException.h"
#include <cstdlib>

int main() {
    try {
        Game game;
        TextObserver textObserver(&game);
        GraphicsObserver GraphicsObserver{&game};

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
    } catch (const UnrecoverableChessException& uce) {
        std::cerr << "Unrecoverable exception: " << uce.what() << '\n';
        return EXIT_FAILURE;
    }
}
