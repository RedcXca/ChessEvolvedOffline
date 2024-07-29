#include "Computer.h"

// Prioritizes avoiding captures, captures, checks
struct Level3 : Computer {
    MoveInput getNextMove(Board&) override;
    using Computer::Computer;
};
