#ifndef TEST_MODEL_BASE_CONTROL_H
#define TEST_MODEL_BASE_CONTROL_H

#include "../_include/test_Base.h"

class ModelBaseControl: public Test {
public:
    TestStatus run ();

private:
    TestStatus BaseTest ();
};

#endif//TEST_MODEL_BASE_CONTROL_H
