#include "Subject.h"
#include "Observer.h"
#include <algorithm>

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}
void Subject::detach(Observer* o) {
    observers.erase(std::find(observers.begin(), observers.end(), o));
}
void Subject::notifyObservers() {
    for (auto& o : observers) o->update();
}
