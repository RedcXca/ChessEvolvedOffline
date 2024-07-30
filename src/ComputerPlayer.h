#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "color.h"
#include "Player.h"
#include <random>
#include "UnrecoverableChessException.h"
struct ComputerPlayer : Player {
    ComputerPlayer(Color color) : color{color} {}

protected:
    Color color;
    MoveInput randomMove(const std::vector<Move>& moves) {
        if (!moves.size()) throw UnrecoverableChessException("No moves possible");
        static std::mt19937 gen(std::random_device{}());
        auto randMove = moves[std::uniform_int_distribution<>(0, moves.size() - 1)(gen)];
        return {randMove.from, randMove.to, randMove.promotionPiece};
    }
};
#endif
