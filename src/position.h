#ifndef POSITION_H
#define POSITION_H
#include <string>
struct Position {
    int x, y;
    std::string toString();
    Position (std::string str);
    Position(int x, int y);
    bool operator==(const Position& other) const;
};
#endif
