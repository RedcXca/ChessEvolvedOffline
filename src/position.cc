#include "position.h"
#include "ChessException.h"

Position::Position(int x, int y) : x(x), y(y) {}

Position::Position(const std::string& str) : x(str.size() != 2 ? throw ChessException{"Position must be exactly 2 characters."} : 'a' <= str[0] && str[0] <= 'h' ? str[0] - 'a' : throw ChessException{"Invalid file."} ), y('1' <= str[1] && str[1] <= '8' ? str[1] - '1' : throw ChessException{"Invalid rank."}) {}

std::string Position::toString() {
    return char(x + 'a') + std::to_string(y + 1);
}
