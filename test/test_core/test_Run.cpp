#include "../_include/test_Run.h"

// Dependencies
#include <algorithm>
#include "../_include/test_Base.h"
#include "../_include/test_List.h"

// Tests
#include "../_include/test_SampleSuite.h"
#include "../_include/test_ModelBaseControl.h"
#include "../_include/test_ModelLogicControl.h"
#include "../_include/test_CycleDetect.h"

void initTest ()
{
    TestList.tests_[TestType::SAMPLE_SUITE] = new SampleSuite();
    TestList.tests_[TestType::MODEL_BASE_CONTROL] = new ModelBaseControl();
    TestList.tests_[TestType::MODEL_LOGIC_CONTROL] = new ModelLogicControl();
    TestList.tests_[TestType::ALG_CYCLE_DETECT] = new Alg_CycleDetect();
}

void runTest ()
{
    std::for_each(TestList.tests_.begin(),
                  TestList.tests_.end(),
                  [] (TestSuite it) {
                      it.second->run();
                  });
}

void cleanTest ()
{
    std::for_each(TestList.tests_.begin(),
                  TestList.tests_.end(),
                  [] (TestSuite it) {
                      delete it.second;
                  });
}
