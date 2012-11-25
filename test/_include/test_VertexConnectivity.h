#ifndef TEST_VERTEX_CONNECTIVITY_H
#define TEST_VERTEX_CONNECTIVITY_H

#include "../_include/test_Base.h"

// Required By Test
#include "../../src/model/_include/LogicController.h"
#include "../../src/model/_include/AlgorithmController.h"

class ut_Alg_VertexConnectivity : public Test {
public:
    ut_Alg_VertexConnectivity ();

    virtual TestStatus run () override;

private:
    TestStatus test1 ();

    Storage             stack_;
    BaseController      base_;
    LogicController     logic_;
    AlgorithmController alg_;
};

#endif//TEST_VERTEX_CONNECTIVITY_H
