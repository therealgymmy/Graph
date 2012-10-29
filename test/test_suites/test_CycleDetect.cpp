#include "../_include/test_CycleDetect.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/model/_include/LogicController.h"
#include "../../src/model/_include/AlgorithmController.h"

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
    Identity g = LogicControl.newGraph();
    Identity v1 = LogicControl.newVertex(g);
    Identity v2 = LogicControl.newVertex(g);
    Identity v3 = LogicControl.newVertex(g);
    Identity v4 = LogicControl.newVertex(g);
    Identity v5 = LogicControl.newVertex(g);

    __checkpoint("Graph Cycle Detection");
    if (LogicControl.join(v1, v2) == false) {
        __log_print << "Cannot join 1 & 2";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(v1, v3) == false) {
        __log_print << "Cannot join 1 & 3";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(v1, v4) == false) {
        __log_print << "Cannot join 1 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(v1, v5) == false) {
        __log_print << "Cannot join 1 & 5";
        __return_status(TestStatus::FAIL);
    }

    if (AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (LogicControl.join(v2, v5) == false) {
        __log_print << "Cannot join 2 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    if (LogicControl.disjoin(v2, v5) == false) {
        __log_print << "Cannot disjoin 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (LogicControl.join(v3, v5) == false) {
        __log_print << "Cannot join 3 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("clean up");
    if (!LogicControl.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus Alg_CycleDetect::test2 ()
{
    __enter;
    __checkpoint("Initialization");
    Identity g = LogicControl.newGraph();
    Identity v1 = LogicControl.newVertex(g);
    Identity v2 = LogicControl.newVertex(g);
    Identity v3 = LogicControl.newVertex(g);
    Identity v4 = LogicControl.newVertex(g);
    Identity v5 = LogicControl.newVertex(g);

    __checkpoint("Graph Cycle Detection");
    if (LogicControl.join(v1, v2) == false) {
        __log_print << "Cannot join 1 & 2";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(v2, v3) == false) {
        __log_print << "Cannot join 2 & 3";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(v3, v4) == false) {
        __log_print << "Cannot join 3 & 4";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.join(v4, v5) == false) {
        __log_print << "Cannot join 4 & 5";
        __return_status(TestStatus::FAIL);
    }

    if (AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (LogicControl.join(v1, v5) == false) {
        __log_print << "Cannot join 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    if (LogicControl.disjoin(v1, v5) == false) {
        __log_print << "Cannot disjoin 1 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Cycle detected although there is no cycle";
        __return_status(TestStatus::FAIL);
    }

    if (LogicControl.join(v3, v5) == false) {
        __log_print << "Cannot join 3 & 5";
        __return_status(TestStatus::FAIL);
    }
    if (!AlgorithmControl.hasCycleAt(g)) {
        __log_print << "Existing cycle undetected";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("clean up");
    if (!LogicControl.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
