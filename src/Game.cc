#include "Game.h"
#include <iostream>
#include <string>
#include "ChessException.h"
#include "HumanPlayer.h"
#include <memory>
#include "color.h"
#include "ComputerLevel1.h"
#include "ComputerLevel2.h"
#include "ComputerLevel3.h"
#include "ComputerLevel4.h"
#include <optional>

Board::SquareState Game::getState(Position p) const {
    return board.getState(p);
}

void Game::setup() {
    for (int x = 0; x < Board::SIZE; ++x)
        for (int y = 0; y < Board::SIZE; ++y)
            board.removePiece(Position{x, y});
    for (std::string command, piece, square; std::cin >> command;) {
        try {
            if (command == "+") {
                std::cin >> piece >> square;
                board.placePiece(Position{square}, piece[0]);
                notifyObservers();
            } else if (command == "-") {
                std::cin >> square;
                if (board.removePiece(Position{square})) notifyObservers();
            } else if (std::string color; command == "=") {
                std::cin >> color;
                if (color == "white")
                    board.setColor(Color::White);
                else if (color == "black")
                    board.setColor(Color::Black);
                else
                    std::cerr << "Invalid color\n";
            } else if (command == "done") {
                std::map<char, int> pieceCount;
                for (auto& piece : board.allPieces) ++pieceCount[piece->toChar()];
                bool badPawn = false;
                for (int x = 0; x < Board::SIZE; ++x)
                    badPawn |= Board::isPiece(board.board[Board::SIZE - 1][x], 'p') || Board::isPiece(board.board[0][x], 'p');
                if (pieceCount['k'] != 1)
                    std::cerr << "There must be exactly 1 black king.\n";
                else if (pieceCount['K'] != 1)
                    std::cerr << "There must be exactly 1 white king.\n";
                else if (badPawn)
                    std::cerr << "No pawns may be on the first or last row of the board.\n";
                else if (!board.validateBoard(Color::White) || !board.validateBoard(Color::Black))
                    std::cerr << "Neither king must be in check.\n";
                else
                    break;
            } else
                std::cerr << "Invalid setup command.\n";
        } catch (const ChessException& ce) {
            std::cerr << ce.what() << '\n';
        }
    }
}

Player* getPlayer(std::string playerType, Color c) {
    if (playerType == "human") return new HumanPlayer;
    if (playerType == "computer1") return new ComputerLevel1{c};
    if (playerType == "computer2") return new ComputerLevel2{c};
    if (playerType == "computer3") return new ComputerLevel3{c};
    if (playerType == "computer4") return new ComputerLevel4{c};
    // TODO: handle computer level 5
    throw ChessException{"Invalid player type."};
}

std::string getColorName(Color c) {
    return c == Color::White ? "White" : "Black";
}

void Game::play(std::map<Color, std::string> players) {
    std::map<Color, std::unique_ptr<Player>> actualPlayers;
    board.generateLegalMoves();
    for (auto& [color, type] : players)
        actualPlayers.emplace(color, getPlayer(type, color));
    notifyObservers();
    for (std::string command; std::cin >> command;) {
        try {
            if (command == "resign") {
                std::cout << getColorName(Board::getNextColor(board.getSide())) << " wins!\n";
                scores[Board::getNextColor(board.getSide())] += 2;
                break;
            } else if (command == "move") {
                auto move = actualPlayers[board.getSide()]->getNextMove(board);
                if (!board.board[move.from.y][move.from.x])
                    std::cerr << "No piece at from square.\n";
                else if (board.board[move.from.y][move.from.x]->getColor() != board.getSide())
                    std::cerr << "Cannot move opponent's piece.\n";
                else {
                    std::optional<Move> actualMove;
                    for (auto legalMove : board.getLegalMoves())
                        if (legalMove.from == move.from && legalMove.to == move.to) {
                            if (legalMove.promotionPiece && !move.promotion) {
                                std::cerr << "Promotion piece not specified.\n";
                                break;
                            } else if (!legalMove.promotionPiece && move.promotion) {
                                std::cerr << "Invalid specification of promotion piece.\n";
                                break;
                            } else if (legalMove.promotionPiece == move.promotion) {
                                actualMove = legalMove;
                                break;
                            }
                        }
                    if (actualMove) {
                        board.makeMove(*actualMove);
                        board.setSelected(Position(-1, -1));
                        notifyObservers();
                        auto nextLegalMoves = board.getLegalMoves();
                        if (actualMove->check) {
                            if (nextLegalMoves.empty()) {
                                std::cout << "Checkmate! " << getColorName(Board::getNextColor(board.getSide())) << " wins!\n";
                                scores[Board::getNextColor(board.getSide())] += 2;
                                break;
                            } else
                                std::cout << getColorName(board.getSide()) << " is in check.\n";
                        } else if (nextLegalMoves.empty()) {
                            std::cout << "Stalemate!\n";
                            for (auto& [color, score] : scores) ++score;
                            break;
                        }
                    } else
                        std::cerr << "Illegal move.\n";
                }
            } else if (command == "undo") {
                board.undoMove();
                notifyObservers();
            } else if (command == "select") {
                std::string position;
                std::cin >> position;
                board.setSelected(Position(position));
                notifyObservers();
            } else if (command == "deselect") {
                board.setSelected(Position(-1, -1));
                notifyObservers();
            } else
                std::cerr << "Invalid command!\n";
        } catch (const ChessException& ce) {
            std::cerr << ce.what() << '\n';
        }
    }
    board = Board{};
}

void Game::reportResults() const {
    std::cout << "Final Score:\n";
    for (auto& [color, score] : scores)
        std::cout << getColorName(color) << ": " << (score / 2) << (score & 1 ? ".5" : "") << '\n'; // avoiding double for precision
}
