#ifndef POSITION_H
#define POSITION_H
#include <string>
struct Position {
    int x, y;
    std::string toString();
    Position(int x, int y) : x(x), y(y) {}
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    };
};
#endif
