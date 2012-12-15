#include "../_include/test_SpanningTree.h"

// Dependencies
#include "../_include/test_Log.h"

ut_Alg_SpanningTree::ut_Alg_SpanningTree ()
: stack_(),
  base_(stack_),
  logic_(base_),
  alg_(logic_)
{
}

TestStatus ut_Alg_SpanningTree::run ()
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

TestStatus ut_Alg_SpanningTree::test1 ()
{
    __enter;
    __checkpoint("Initialization");
    Identity g = logic_.newGraph();
    Identity v1 = logic_.newVertex(g);
    Identity v2 = logic_.newVertex(g);
    Identity v3 = logic_.newVertex(g);
    Identity v4 = logic_.newVertex(g);
    Identity v5 = logic_.newVertex(g);

    __checkpoint("Simple Spanning Tree Detection");
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
    if (logic_.join(v2, v5) == false) {
        __log_print << "Cannot join 2 & 5";
        __return_status(TestStatus::FAIL);
    }

    Identity tree = alg_.spanningTreeAt(g);
    __print_graph(logic_, g);
    __print_graph(logic_, tree);

    __checkpoint("clean up");
    if (!logic_.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ut_Alg_SpanningTree::test2 ()
{
    __enter;
    __checkpoint("Initialization");
    Identity g = logic_.newGraph();
    Identity v1 = logic_.newVertex(g);
    Identity v2 = logic_.newVertex(g);
    Identity v3 = logic_.newVertex(g);
    Identity v4 = logic_.newVertex(g);
    Identity v5 = logic_.newVertex(g);
    Identity v6 = logic_.newVertex(g);
    Identity v7 = logic_.newVertex(g);
    Identity v8 = logic_.newVertex(g);
    Identity v9 = logic_.newVertex(g);

    __checkpoint("Simple Spanning Tree Detection");
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
    if (logic_.join(v1, v6) == false) {
        __log_print << "Cannot join 1 & 6";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v1, v7) == false) {
        __log_print << "Cannot join 1 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v1, v8) == false) {
        __log_print << "Cannot join 1 & 8";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v1, v9) == false) {
        __log_print << "Cannot join 1 & 9";
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
    if (logic_.join(v5, v6) == false) {
        __log_print << "Cannot join 5 & 6";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v6, v7) == false) {
        __log_print << "Cannot join 6 & 7";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v7, v8) == false) {
        __log_print << "Cannot join 7 & 8";
        __return_status(TestStatus::FAIL);
    }
    if (logic_.join(v8, v9) == false) {
        __log_print << "Cannot join 8 & 9";
        __return_status(TestStatus::FAIL);
    }

    Identity tree = alg_.spanningTreeAt(g);
    __print_graph(logic_, g);
    __print_graph(logic_, tree);

    __checkpoint("clean up");
    if (!logic_.remGraph(g)) {
        __log_print << "Cannot remove Graph";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
