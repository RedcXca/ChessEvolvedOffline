#include "Game.h"
#include <iostream>
#include <string>
#include "ChessException.h"
#include "HumanPlayer.h"
#include <memory>

char Game::getState(Position p) const {
    return board.getState(p);
}

void Game::setup() {
    for (int x = 0; x < Board::SIZE; ++x)
        for (int y = 0; y < Board::SIZE; ++y)
            board.removePiece(Position{x, y});
    for (std::string command, piece, square; std::cin >> command && command != "done";) {
        try {
            if (command == "+") {
                std::cin >> piece >> square;
                board.placePiece(Position{square}, piece[0]);
            } else if (command == "-") {
                std::cin >> square;
                board.removePiece(Position{square});
            } else if (std::string color; command == "=") {
                std::cin >> color;
                if (color == "white")
                    board.setColor(Color::White);
                else if (color == "black")
                    board.setColor(Color::Black);
                else
                    std::cerr << "Invalid color\n";
            } else
                std::cerr << "Invalid setup command.\n";
        } catch (const ChessException& ce) {
            std::cerr << ce.what() << '\n';
        }
    }
}

Player* getPlayer(std::string playerType, Color c) {
    if (playerType == "human") return new HumanPlayer{c};
    // TODO: handle computers
    throw ChessException{"Invalid player type."};
}

std::string getColorName(Color c) {
    return c == Color::White ? "White" : "Black";
}

void Game::play(std::map<Color, std::string> players) {
    std::map<Color, std::unique_ptr<Player>> actualPlayers;
    for (auto& [color, type] : players)
        actualPlayers.emplace(color, getPlayer(type, color));
    auto getOppositeColor = [](Color c) {
        return c == Color::White ? Color::Black : Color::White;
    };
    notifyObservers();
    for (std::string command; std::cin >> command;) {
        try {
            if (command == "resign") {
                std::cout << getColorName(getOppositeColor(board.getSide())) << " wins!\n";
            } else if (command == "move") {
                auto move = actualPlayers[board.getSide()]->getNextMove(board);
                if (!board.board[move.from.y][move.from.x]) std::cerr << "No piece at from square.\n";
                else if (board.board[move.from.y][move.from.x]->getColor() != board.getSide()) std::cerr << "Cannot move opponent's piece.\n";
                else {
                    bool works = false;
                    for (auto legalMove : board.generateLegalMoves())
                        if (legalMove.from == move.from && legalMove.to == move.to) {
                            works = true;
                            board.makeMove(legalMove);
                            break;
                        }
                    if (works) {
                        notifyObservers();
                        auto nextLegalMoves = board.generateLegalMoves();
                        if (board.checkThreatened(board.kingPositions.at(board.getSide()))[getOppositeColor(board.getSide())]) {
                            if (nextLegalMoves.empty()) {
                                std::cout << "Checkmate! " << getColorName(getOppositeColor(board.getSide())) << " wins!\n";
                                scores[getOppositeColor(board.getSide())] += 2;
                            } else
                                std::cout << getColorName(board.getSide()) << " is in check.\n";
                        } else if (nextLegalMoves.empty()) {
                            std::cout << "Stalemate!\n";
                            for (auto& [color, score] : scores) ++score;
                            break;
                        }
                    } else std::cerr << "Illegal move.\n";
                }
            } else std::cerr << "Invalid command!\n";
        } catch (const ChessException& ce) {
            std::cerr << ce.what() << '\n';
        }
    }
    board = Board{};
}

void Game::reportResults() const {
    std::cout << "Final Score:\n";
    for (auto& [color, score] : scores)
        std::cout << getColorName(color) << ": " << (score / 2) << (score & 1 ? ".5" : "") << '\n';
}
