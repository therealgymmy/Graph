#ifndef TEST_MODEL_LOGIC_CONTROL_H
#define TEST_MODEL_LOGIC_CONTROL_H

#include "../_include/test_Base.h"

class ModelLogicControl: public Test {
public:
    TestStatus run ();

private:
    TestStatus LogicTest ();
};

#endif//TEST_MODEL_LOGIC_CONTROL_H
