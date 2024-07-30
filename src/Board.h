#ifndef BOARD_H
#define BOARD_H
#include "move.h"
#include <vector>
#include <array>
#include <map>
#include "color.h"
#include "position.h"
#include <memory>
#include <string>
#include <iostream>

struct Board {
    friend class Game;
    static inline constexpr int SIZE = 8;
    static constexpr auto PROMOTION_CHOICES = {'Q', 'N', 'B', 'R'};
    explicit Board(const std::string& fileName = "initialState.txt");
    bool validateBoard(Color side);
    std::map<Color, int> checkThreatened(Position);
    std::map<Color, std::vector<Piece*>> checkThreatenedPieces(Position pos);
    const std::vector<Move>& getLegalMoves();
    void makeMove(Move);
    void undoMove();
    Color getSide() const;
    static inline Color getNextColor(Color color) {
        return Color(int(color) ^ 1); // can be generalized for more colors
    }
    static inline bool isPiece(Piece* piece, char p) {
        return piece && std::tolower(piece->toChar()) == p;
    }
    void printBoard() { // for debugging
        for (int i = SIZE - 1; i >= 0; i--) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << (board[i][j] ? board[i][j]->toChar() : ' ');
            }
            std::cout << std::endl;
        }
    }
    struct SquareState {
        char piece;
        bool highlighted;
        bool operator==(const SquareState& other) const = default;
    };
    SquareState getState(Position) const;
    Position getSelected();
    void setSelected(Position p);

private:
    Position selected = {-1, -1};
    std::vector<Move> history;
    std::vector<Move> legalMoves;
    std::vector<std::vector<Move>> legalMoveHistory;
    const std::vector<Move>& generateLegalMoves();
    void testUndo();
    void testMove(Move);
    std::array<std::array<Piece*, SIZE>, SIZE> board{};
    std::map<Color, Position> kingPositions;
    std::vector<std::unique_ptr<Piece>> allPieces;
    Position enPassantSquare{-1, -1};
    Color currColor{};
    bool checkBlocked(Position, int deltaX, int deltaY, bool attackable = false, Color otherSide = Color::White);
    bool placePiece(Position, char);
    bool removePiece(Position);
    void setColor(Color);
    template<typename Func> void checkThreatenedImpl(Position pos, Func func);
};
#endif
