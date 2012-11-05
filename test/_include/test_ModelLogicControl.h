#ifndef TEST_MODEL_LOGIC_CONTROL_H
#define TEST_MODEL_LOGIC_CONTROL_H

#include "../_include/test_Base.h"

class ModelLogicControl: public Test {
public:
    virtual TestStatus run () override;

private:
    TestStatus GraphCreation ();
    TestStatus VertexCreation ();
    TestStatus VertexConnection ();
    TestStatus VertexDisconnection ();
    TestStatus VertexRemoval ();
    TestStatus GraphRemoval ();
};

#endif//TEST_MODEL_LOGIC_CONTROL_H
