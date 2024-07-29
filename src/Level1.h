#include "computer.h"

struct Level1 : Computer {
    MoveInput getNextMove(Board&) override;
    using Computer::Computer;
};
