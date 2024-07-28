#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}
void Subject::detach(Observer* o) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}
void Subject::notifyObservers() {
    for (auto& o : observers) o->update();
}
