#ifndef TEST_CONTROLLER_H
#define TEST_CONTROLLER_H

#include "../_include/test_Base.h"

// Required By Test
#include "../../src/controller/_include/Controller.h"

class ControllerTest: public Test {
public:
    virtual TestStatus run () override;

private:
    TestStatus exceptionSafe (Controller *control);
};

#endif//TEST_CONTROLLER_H
