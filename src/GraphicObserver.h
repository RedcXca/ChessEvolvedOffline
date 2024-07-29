#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "Observer.h"
#include "Game.h"
#include "Window.h"

struct GraphicsObserver : Observer {
    // TODO: Xwindow window;
    void update();
    using Observer::Observer;
};

#endif
