#ifndef TEST_CYCLE_DETECT_H
#define TEST_CYCLE_DETECT_H

#include "../_include/test_Base.h"

// Required By Test
#include "../../src/model/_include/AlgorithmController.h"
#include "../../src/model/_include/LogicController.h"

class Alg_CycleDetect : public Test {
public:
    Alg_CycleDetect ();

    virtual TestStatus run () override;

private:
    TestStatus test1 ();
    TestStatus test2 ();

    Storage             stack_;
    BaseController      base_;
    LogicController     logic_;
    AlgorithmController alg_;
};

#endif//TEST_CYCLE_DETECT_H
