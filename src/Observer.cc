#include "Observer.h"
#include "Game.h"

Observer::Observer(Game* g) : game{g} {
    game->attach(this);
};

Observer::~Observer() {
    game->detach(this);
}
