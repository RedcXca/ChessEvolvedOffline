#include "Player.h"
#include <random>

struct Computer : Player {
    protected:
    MoveInput randomMove(const std::vector<Move>& moves) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(0, moves.size() - 1);
        return {moves[dis(gen)].from, moves[dis(gen)].to, moves[dis(gen)].promotionPiece};
    }
    using Player::Player;
};
