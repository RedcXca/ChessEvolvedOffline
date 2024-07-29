#ifndef MOVEINPUT_H
#define MOVEINPUT_H
#include "position.h"
struct MoveInput {
    Position from, to;
    char promotion;
};
#endif
