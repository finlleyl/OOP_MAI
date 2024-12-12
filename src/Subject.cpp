#include "Subject.hpp"
#include "Observer.hpp"

void Subject::attach(Observer* o) {
    observers.push_back(o);
}

void Subject::detach(Observer* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::notify(const std::string& msg) {
    for (auto& o : observers) o->update(msg);
}