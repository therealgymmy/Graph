#include "../_include/test_CycleDetect.h"

// Dependencies
#include "../_include/test_Log.h"

Alg_CycleDetect::Alg_CycleDetect ()
: stack_(),
  base_(stack_),
  logic_(base_),
  alg_(logic_)
{
}

TestStatus Alg_CycleDetect::run ()
{
    __enter;

    TestStatus testStatus = TestStatus::FAIL;
    if (!((testStatus = test1()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }
    if (!((testStatus = test2()) == TestStatus::PASS)) {
        __return_status(testStatus);
    }

    __return_status(TestStatus::PASS);
}

TestStatus Alg_CycleDetect::test1 ()
{
    __enter;
    __checkpoint("Initialization");
    Identity g = logic_.newGraph();
    Identity v1 = logic_.newVertex(g);
    Identity v2 = logic_.newVertex(g);
    Identity v3 = logic_.newVertex(g);
    Identity v4 = logic_.newVertex(g);
    Identity v5 = logic_.newVertex(g);

    __checkpoint("Graph Cycle Detection");
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
    if (logic_.join(v1, v5) == false) {
        __log_print << "Cannot join 1 & 5";
        __return_status(TestStatus::FAIL);
    }

    if (alg_.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.join(v2, v5) == false) {
        __log_print << "Cannot join 2 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!alg_.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.disjoin(v2, v5) == false) {
        __log_print << "Cannot disjoin 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (alg_.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.join(v3, v5) == false) {
        __log_print << "Cannot join 3 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!alg_.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("clean up");
    if (!logic_.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus Alg_CycleDetect::test2 ()
{
    __enter;
    __checkpoint("Initialization");
    Identity g = logic_.newGraph();
    Identity v1 = logic_.newVertex(g);
    Identity v2 = logic_.newVertex(g);
    Identity v3 = logic_.newVertex(g);
    Identity v4 = logic_.newVertex(g);
    Identity v5 = logic_.newVertex(g);

    __checkpoint("Graph Cycle Detection");
    if (logic_.join(v1, v2) == false) {
        __log_print << "Cannot join 1 & 2";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v2, v3) == false) {
        __log_print << "Cannot join 2 & 3";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v3, v4) == false) {
        __log_print << "Cannot join 3 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v4, v5) == false) {
        __log_print << "Cannot join 4 & 5";
        __return_status(TestStatus::FAIL);
    }

    if (alg_.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.join(v1, v5) == false) {
        __log_print << "Cannot join 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!alg_.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.disjoin(v1, v5) == false) {
        __log_print << "Cannot disjoin 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (alg_.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (logic_.join(v3, v5) == false) {
        __log_print << "Cannot join 3 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!alg_.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("clean up");
    if (!logic_.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
