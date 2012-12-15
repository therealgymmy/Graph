#ifndef TEST_SPANNING_TREE_H
#define TEST_SPANNING_TREE_H

#include "../_include/test_Base.h"

// Required By Test
#include "../../src/model/_include/LogicController.h"
#include "../../src/model/_include/AlgorithmController.h"

class ut_Alg_SpanningTree : public Test {
public:
    ut_Alg_SpanningTree ();

    virtual TestStatus run () override;

private:
    TestStatus test1 ();
    TestStatus test2 ();

    Storage             stack_;
    BaseController      base_;
    LogicController     logic_;
    AlgorithmController alg_;
};

#endif//TEST_SPANNING_TREE_H
