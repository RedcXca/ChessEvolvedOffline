#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "position.h"

class Observer;

class Subject {
    std::vector<Observer*> observers;

public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    virtual char getState(Position p) const = 0;
    virtual ~Subject() = default;
};

#endif
