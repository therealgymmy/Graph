#ifndef TEST_SAMPLE_SUITE_H
#define TEST_SAMPLE_SUITE_H

#include "../_include/test_Base.h"

class SampleSuite: public Test {
public:
    virtual TestStatus run();

private:
    // Put additional support functions here.
    TestStatus support_1();
    TestStatus support_2();
};

#endif//TEST_SAMPLE_SUITE_H
