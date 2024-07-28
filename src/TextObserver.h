#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "Observer.h"
#include "Subject.h"

struct TextObserver : Observer {
    TextObserver(Subject*);
    void update();
};

#endif
