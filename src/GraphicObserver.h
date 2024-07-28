#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "Observer.h"
#include "Subject.h"
#include "Window.h"

struct GraphicsObserver : Observer {
    // TODO: Xwindow window;
    GraphicsObserver(Subject*);
    void update();
};

#endif
