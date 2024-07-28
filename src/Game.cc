#include "Game.h"

Game::Game() {
   // TODO
}

char Game::getState(Position p) const {
    return board->getState(p);
}

const Board& Game::getBoard() const {
    return *board;
}
