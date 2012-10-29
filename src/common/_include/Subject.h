#ifndef SUBJECT_H
#define SUBJECT_H

// Dependencies
#include <set>
#include "Observer.h"

class Subject {
public:
    virtual ~Subject () = default;
    Subject (const Subject &rhs) = delete;
    Subject& operator=(const Subject &rhs) = delete;

    void subscribe   (Observer *obs);
    void unsubscribe (Observer *obs);

protected:
    Subject () {}

    void notify ();

private:
    std::set<Observer*> subscribers_;
};

#endif//SUBJECT_H
