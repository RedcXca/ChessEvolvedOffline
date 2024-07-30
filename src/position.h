#ifndef POSITION_H
#define POSITION_H
#include <string>
struct Position {
    int x, y;
    std::string toString();
    Position(const std::string& str);
    Position(int x, int y);
    bool operator==(const Position& other) const = default;
};
#endif
