#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "Observer.h"
#include "Game.h"

struct TextObserver : Observer {
    void update();
    using Observer::Observer;
};

#endif
