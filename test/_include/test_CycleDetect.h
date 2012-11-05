#ifndef TEST_CYCLE_DETECT_H
#define TEST_CYCLE_DETECT_H

#include "../_include/test_Base.h"

class Alg_CycleDetect : public Test {
public:
    virtual TestStatus run () override;

private:
    TestStatus test1 ();
    TestStatus test2 ();
};

#endif//TEST_CYCLE_DETECT_H
