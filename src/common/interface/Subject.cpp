#include "../_include/Subject.h"

// Dependencies
#include <algorithm>

void Subject::notify ()
{
    std::for_each(subscribers_.begin(), subscribers_.end(),
                  [] (Observer *obs) {
                      obs->update();
                  });
}

void Subject::subscribe (Observer *obs)
{
    subscribers_.insert(obs);
}

void Subject::unsubscribe (Observer *obs)
{
    auto it = subscribers_.find(obs);
    if (it != subscribers_.end()) {
        subscribers_.erase(it);
    }
}
