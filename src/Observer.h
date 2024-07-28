#ifndef OBSERVER_H
#define OBSERVER_H
class Subject;

class Observer {
protected:
    Subject* subject;

public:
    Observer(Subject* s);
    virtual void update() = 0;
    virtual ~Observer();
};

#endif
