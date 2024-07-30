#ifndef GAME_H
#define GAME_H
#include "Subject.h"
#include "Board.h"
#include <map>
class Game : public Subject {
    Board board;
    std::map<Color, int> scores{{Color::White, 0}, {Color::Black, 0}};

public:
    char getState(Position p) const;
    void setup();
    void play(std::map<Color, std::string> players);
    void reportResults() const;
};
#endif
