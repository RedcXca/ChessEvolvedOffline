#include "Observer.h"
#include "Subject.h"

Observer::Observer(Subject* s) : subject{s} {
    subject->attach(this);
};

Observer::~Observer() {
    subject->detach(this);
}
