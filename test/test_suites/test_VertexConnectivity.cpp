#include "../_include/test_VertexConnectivity.h"

// Dependencies
#include "../_include/test_Log.h"

ut_Alg_VertexConnectivity::ut_Alg_VertexConnectivity ()
: stack_(),
  base_(stack_),
  logic_(base_),
  alg_(logic_)
{
}

TestStatus ut_Alg_VertexConnectivity::run ()
{
    __enter;

    TestStatus testStatus = TestStatus::FAIL;
    if (!((testStatus = test1()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ut_Alg_VertexConnectivity::test1 ()
{
    __enter;
    __checkpoint("Initialization");
    Identity g = logic_.newGraph();
    Identity v1 = logic_.newVertex(g);
    Identity v2 = logic_.newVertex(g);
    Identity v3 = logic_.newVertex(g);
    Identity v4 = logic_.newVertex(g);
    Identity v5 = logic_.newVertex(g);

    __checkpoint("Vertex Path Detection");
    if (logic_.join(v1, v2) == false) {
        __log_print << "Cannot join 1 & 2";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v1, v3) == false) {
        __log_print << "Cannot join 1 & 3";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v1, v4) == false) {
        __log_print << "Cannot join 1 & 4";
        __return_status(TestStatus::FAIL);
    }

    if (alg_.hasPathBetween(v1, v5, g)) {
        __log_print << "Path detected between 1 & 5 although they are not connected";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.join(v1, v5) == false) {
        __log_print << "Cannot join 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!alg_.hasPathBetween(v1, v5, g)) {
        __log_print << "Existing path between 1 & 5 undetected";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.join(v2, v5) == false) {
        __log_print << "Cannot join 2 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!alg_.hasPathBetween(v2, v5, g)) {
        __log_print << "Existing path between 2 & 5 undetected";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.disjoin(v2, v5) == false) {
        __log_print << "Cannot disjoin 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.disjoin(v2, v1) == false) {
        __log_print << "Cannot disjoin 2 & 1";
        __return_status(TestStatus::FAIL);
    }
    if (alg_.hasPathBetween(v2, v5, g)) {
        __log_print << "Path detected between 2 & 5 although they are not connected";
        __return_status(TestStatus::FAIL);
    }

    if (!alg_.hasPathBetween(v3, v5, g)) {
        __log_print << "Existing path between 3 & 5 undetected";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("clean up");
    if (!logic_.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
