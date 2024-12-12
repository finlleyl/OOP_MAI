#pragma once
#include <vector>
#include <string>
#include <algorithm>

class Observer;

class Subject {
    std::vector<Observer*> observers;
public:
    void attach(Observer*);
    void detach(Observer*);
protected:
    void notify(const std::string&);
};