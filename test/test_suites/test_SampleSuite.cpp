#include "../_include/test_SampleSuite.h"

// Dependencies
#include "../_include/test_Log.h"

// Required By Test
// #include "../../src/Program_Header_Files_You_Need"

TestStatus SampleSuite::run ()
{
    __enter;
    __checkpoint("A checkpoint keeps track of test progress.");
    if (support_1() != TestStatus::SUCCESS) {
        __log_print << "support_1 failed.";
    }
    if (support_2() != TestStatus::SUCCESS) {
        __log_print << "support_2 failed.";
    }
    __return(TestStatus::SUCCESS);
}

TestStatus SampleSuite::support_1 ()
{
    __enter;
    // More tests.
    __return(TestStatus::SUCCESS);
}

TestStatus SampleSuite::support_2 ()
{
    __enter;
    // More tests.
    __return(TestStatus::SUCCESS);
}
