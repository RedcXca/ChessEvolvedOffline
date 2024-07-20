#include "piece.h"
#include "partialmove.h"
#include <vector>

void Piece::pushBishopMoves(std::vector<PartialMove>& moves, int range, MoveType type, int innerRange) {
    for (int i = innerRange; i <= range; i++) {
        moves.push_back({i, i, type});
        moves.push_back({i, -i, type});
        moves.push_back({-i, i, type});
        moves.push_back({-i, -i, type});
    }
}

void Piece::pushRookMoves(std::vector<PartialMove>& moves, int range, MoveType type, int innerRange) {
    for (int i = innerRange; i <= range; i++) {
        moves.push_back({i, 0, type});
        moves.push_back({-i, 0, type});
        moves.push_back({0, i, type});
        moves.push_back({0, -i, type});
    }
}

void Piece::pushKingMoves(std::vector<PartialMove>& moves, MoveType type) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            moves.push_back({dx, dy, type});
        }
    }
}

void Piece::pushKnightMoves(std::vector<PartialMove>& moves, MoveType type) {
    moves.push_back({2, 1, type});
    moves.push_back({2, -1, type});
    moves.push_back({-2, 1, type});
    moves.push_back({-2, -1, type});
    moves.push_back({1, 2, type});
    moves.push_back({1, -2, type});
    moves.push_back({-1, 2, type});
    moves.push_back({-1, -2, type});
}

void Piece::pushValkyrieMoves(std::vector<PartialMove>& moves, MoveType type) {
    moves.push_back({3, 1, type});
    moves.push_back({3, -1, type});
    moves.push_back({-3, 1, type});
    moves.push_back({-3, -1, type});
    moves.push_back({1, 3, type});
    moves.push_back({1, -3, type});
    moves.push_back({-1, 3, type});
    moves.push_back({-1, -3, type});
}

void Piece::pushZebraMoves(std::vector<PartialMove>& moves, MoveType type) {
    moves.push_back({3, 2, type});
    moves.push_back({3, -2, type});
    moves.push_back({-3, 2, type});
    moves.push_back({-3, -2, type});
    moves.push_back({2, 3, type});
    moves.push_back({2, -3, type});
    moves.push_back({-2, 3, type});
    moves.push_back({-2, -3, type});
}
