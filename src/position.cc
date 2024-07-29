#include "position.h"

Position::Position(int x, int y) : x(x), y(y) {}
Position::Position(std::string str) : x(str[0] - 'a'), y(str[1] - '1') {}
bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}
std::string Position::toString() {
    return std::string(1, x + 'a') + std::to_string(y + 1);
}
