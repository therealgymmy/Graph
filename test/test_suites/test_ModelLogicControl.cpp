#include "../_include/test_ModelLogicControl.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
#include "../../src/model/_include/LogicController.h"

TestStatus ModelLogicControl::run ()
{
    __enter;

    TestStatus testStatus = TestStatus::FAIL;

    if (!((testStatus = LogicTest()) == TestStatus::PASS)) {
        __log_print << "Test failed at LogicTest.";
    }

    __return_status(testStatus);
}

TestStatus ModelLogicControl::LogicTest ()
{
    __enter;
    __checkpoint("New Graph Creation");
    Identity g1 = LogicControl.newGraph();
    if (g1 != 1) {
        __log_print << "Graph_1 id != 1";
        __return_status(TestStatus::FAIL);
    }
    Identity g2 = LogicControl.newGraph();
    if (g2 != 2) {
        __log_print << "Graph_2 id != 2";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("New Vertex Creation");
    Identity v1 = LogicControl.newVertex(1);
    if (v1 != 3) {
        __log_print << "Vertex_1 id != 3";
        __return_status(TestStatus::FAIL);
    }
    Identity v2 = LogicControl.newVertex(1);
    if (v2 != 4) {
        __log_print << "Vertex_2 id != 4";
        __return_status(TestStatus::FAIL);
    }
    Identity v3 = LogicControl.newVertex(2);
    if (v3 != 5) {
        __log_print << "Vertex_3 id != 5";
        __return_status(TestStatus::FAIL);
    }
    Identity v4 = LogicControl.newVertex(2);
    if (v4 != 6) {
        __log_print << "Vertex_4 id != 6";
        __return_status(TestStatus::FAIL);
    }
    Identity v5 = LogicControl.newVertex(2);
    if (v5 != 7) {
        __log_print << "Vertex_5 id != 7";
        __return_status(TestStatus::FAIL);
    }



    __checkpoint("Remove Vertex");
    if (!LogicControl.remVertex(3)) {
        __log_print << "Cannot remove Vertex_1";
        __return_status(TestStatus::FAIL);
    }
    if (!LogicControl.remVertex(6)) {
        __log_print << "Cannot remove Vertex_4";
        __return_status(TestStatus::FAIL);
    }
    if (LogicControl.remVertex(3)) {
        __log_print << "Vertex_1 was removed twice";
        __return_status(TestStatus::FAIL);
    }


    __checkpoint("Remove Graph");
    if (!LogicControl.remGraph(1)) {
        __log_print << "Cannot remove Graph_1";
        __return_status(TestStatus::FAIL);
    }
    if (!LogicControl.remGraph(2)) {
        __log_print << "Cannot remove Graph_2";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
