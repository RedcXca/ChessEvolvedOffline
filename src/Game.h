#ifndef GAME_H
#define GAME_H

#include "Subject.h"
#include "Board.h"

class Game : public Subject {
private:
    Board* board;

public:
    Game();
    char getState(Position p) const;
    const Board& getBoard() const;
};

#endif
