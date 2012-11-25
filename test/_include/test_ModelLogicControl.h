#ifndef TEST_MODEL_LOGIC_CONTROL_H
#define TEST_MODEL_LOGIC_CONTROL_H

#include "../_include/test_Base.h"

// Required By Test
#include "../../src/model/_include/LogicController.h"

class ModelLogicControl: public Test {
public:
    ModelLogicControl ();

    virtual TestStatus run () override;

private:
    Storage         stack_;
    BaseController  base_;
    LogicController logic_;

    TestStatus GraphCreation ();
    TestStatus VertexCreation ();
    TestStatus VertexConnection ();
    TestStatus VertexDisconnection ();
    TestStatus VertexRemoval ();
    TestStatus GraphRemoval ();
};

#endif//TEST_MODEL_LOGIC_CONTROL_H
