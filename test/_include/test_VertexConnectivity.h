#ifndef TEST_VERTEX_CONNECTIVITY_H
#define TEST_VERTEX_CONNECTIVITY_H

#include "../_include/test_Base.h"

class ut_Alg_VertexConnectivity : public Test {
public:
    virtual TestStatus run () override;

private:
    TestStatus test1 ();
};

#endif//TEST_VERTEX_CONNECTIVITY_H
