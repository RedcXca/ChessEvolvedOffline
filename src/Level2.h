#include "Computer.h"

struct Level2 : Computer {
    MoveInput getNextMove(Board&) override;
    using Computer::Computer;
};
