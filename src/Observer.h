#ifndef OBSERVER_H
#define OBSERVER_H
class Game;

class Observer {
protected:
    Game* game;

public:
    Observer(Game* g);
    virtual void update() = 0;
    virtual ~Observer();
};

#endif
