#include "Computer.h"

// Prioritizes captures, checks
struct Level2 : Computer {
    MoveInput getNextMove(Board&) override;
    using Computer::Computer;
};
