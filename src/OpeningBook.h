#ifndef OPENINGBOOK_H
#define OPENINGBOOK_H
#include <vector>
#include <utility>
#include <istream>
#include <string>
#include "position.h"
class OpeningBook {
    void readOpenings(std::istream& is);
    std::vector<std::vector<std::pair<Position, Position>>> openings;
    decltype(openings)::size_type moveIndex{};

public:
    OpeningBook(const std::string& filename);
    OpeningBook(std::istream& is);
    void filterOpenings(std::pair<Position, Position> movePositions);
    const decltype(openings)& getOpenings() const;
    decltype(moveIndex) getMoveIndex() const;
    decltype(openings) getMatchingOpenings(decltype(openings)::value_type movesSoFar) const;
};
#endif
