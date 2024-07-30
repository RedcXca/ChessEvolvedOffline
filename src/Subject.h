#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "position.h"
#include "Board.h"

class Observer;

class Subject {
    std::vector<Observer*> observers;

public:
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    virtual Board::SquareState getState(Position p) const = 0;
    virtual ~Subject() = default;
};

#endif
