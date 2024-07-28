#include <iostream>
#include "Game.h"
#include "Observer.h"
#include "TextObserver.h"
#include "GraphicObserver.h"
#include "Subject.h"

int main() {
    Game game;
    TextObserver textObserver(&game);
    GraphicsObserver graphicsObserver(&game);

    // game.attach(textObserver);
    // TODO: attach graphicsObserver
    // TODO: game.play();
}
