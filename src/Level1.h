#include "Computer.h"

// Totally random moves
struct Level1 : Computer {
    MoveInput getNextMove(Board&) override;
    using Computer::Computer;
};
