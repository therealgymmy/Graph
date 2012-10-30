#include "../_include/test_Controller.h"

// Dependencies
#include "../_include/test_Log.h"

TestStatus ControllerTest::run ()
{
    __enter;

    __checkpoint("Initialization");
    Controller control(&LogicControl, &AlgorithmControl);

    TestStatus testStatus = TestStatus::FAIL;
    if (!((testStatus = exceptionSafe(&control)) == TestStatus::PASS)) {
        __return_status(testStatus);
    }

    __return_status(TestStatus::PASS);
}

TestStatus ControllerTest::exceptionSafe (Controller *control)
{
    __enter;
    __checkpoint("Exception Safe Testing");

    __checkpoint("Obtain graph of non-existent vertex");
    try {
        Result result = control->graphOf(NULL_IDENTITY);
        if (result) {
            __log_print << "Result should be false";
            __return_status(TestStatus::FAIL);
        }
    }
    catch (...) {
        __log_print << "Exception thrown.";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("Obtain vertices from non-existent graph");
    try {
        Result result = control->verticesOf(NULL_IDENTITY);
        if (result) {
            __log_print << "Result should be false";
            __return_status(TestStatus::FAIL);
        }
    }
    catch (...) {
        __log_print << "Exception thrown.";
        __return_status(TestStatus::FAIL);
    }

    __checkpoint("Obtain neighbours from non-existent vertex");
    try {
        Result result = control->neighboursOf(NULL_IDENTITY);
        if (result) {
            __log_print << "Result should be false";
            __return_status(TestStatus::FAIL);
        }
    }
    catch (...) {
        __log_print << "Exception thrown.";
        __return_status(TestStatus::FAIL);
    }

    __return_status(TestStatus::PASS);
}
