#include "OpeningBook.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
OpeningBook::OpeningBook(const std::string& filename) {
    std::ifstream fs{filename};
    readOpenings(fs);
}

OpeningBook::OpeningBook(std::istream& is) {
    readOpenings(is);
}

void OpeningBook::readOpenings(std::istream& is) {
    for (std::string line; getline(is, line);) {
        if (line.empty()) continue;
        std::istringstream ss{line};
        openings.emplace_back();
        for (std::string from, to; ss >> from >> to;)
            openings.back().emplace_back(Position{from}, Position{to});
    }
}

void OpeningBook::filterOpenings(std::pair<Position, Position> movePositions) {
    ++moveIndex;
    std::erase_if(openings, [&](const auto& opening){
        return moveIndex >= opening.size() || opening[moveIndex - 1] != movePositions;
    });
}

auto OpeningBook::getOpenings() const -> const decltype(openings)& {
    return openings;
}

auto OpeningBook::getMoveIndex() const -> decltype(moveIndex) {
    return moveIndex;
}

auto OpeningBook::getMatchingOpenings(decltype(openings)::value_type movesSoFar) const -> decltype(openings) {
    decltype(openings) result;
    std::ranges::copy_if(openings, std::back_inserter(result), [&](const auto& opening) {
        return opening.size() > movesSoFar.size() && std::equal(movesSoFar.begin(), movesSoFar.end(), opening.begin());
    });
    return result;
}
