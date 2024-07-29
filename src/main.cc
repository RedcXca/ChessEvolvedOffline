#include <iostream>
#include <string>
#include "Game.h"
#include "Observer.h"
#include "TextObserver.h"
#include "GraphicObserver.h"
#include "Subject.h"

int main() {
    Game game;
    TextObserver textObserver(&game);
    // GraphicsObserver graphicsObserver(&game);
    // game.attach(&graphicsObserver);

    game.notifyObservers();

    // bool activeGame = false;
    // for (std::string command; std::cin >> command;) {
    //     if (command == "game") {
    //         if (activeGame)
    //             std::cerr << "There is already an active game.\n";
    //         else {
    //             activeGame = true;
    //         }
    //     } else if (command == "setup") {
    //         if (activeGame)
    //             std::cerr << "There is already an active game.\n";
    //         else {
    //             game.setup();
    //         }
    //     } else
    //         std::cerr << "Invalid command!\n";
    // }
}
