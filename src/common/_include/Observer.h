#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer () = default;
    Observer (const Observer &rhs) = delete;
    Observer& operator=(const Observer &rhs) = delete;

    virtual void update () = 0;

protected:
    Observer () {}
};

#endif//OBSERVER_H
