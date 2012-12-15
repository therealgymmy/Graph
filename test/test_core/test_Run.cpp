#include "../_include/test_Run.h"

// Dependencies
#include <algorithm>
#include "../_include/test_Base.h"
#include "../_include/test_List.h"

//---Tests---

#include "../_include/test_SampleSuite.h"
// Model
#include "../_include/test_ModelBaseControl.h"
#include "../_include/test_ModelLogicControl.h"
// Algorithms
#include "../_include/test_CycleDetect.h"
#include "../_include/test_VertexConnectivity.h"
#include "../_include/test_SpanningTree.h"
// Controller
#include "../_include/test_Controller.h"
// View
#include "../_include/test_ViewConsoleControl.h"
#include "../_include/test_ViewCmdParser.h"

void initTest ()
{
    TestList.tests_[TestType::SAMPLE_SUITE] = new SampleSuite();

    TestList.tests_[TestType::MODEL_BASE_CONTROL] = new ModelBaseControl();
    TestList.tests_[TestType::MODEL_LOGIC_CONTROL] = new ModelLogicControl();

    TestList.tests_[TestType::ALG_CYCLE_DETECT] = new Alg_CycleDetect();
    TestList.tests_[TestType::ALG_VERTEX_CONNECTIVITY] = new ut_Alg_VertexConnectivity();
    TestList.tests_[TestType::ALG_SPANNING_TREE] = new ut_Alg_SpanningTree();

    TestList.tests_[TestType::CONTROLLER] = new ControllerTest();

    TestList.tests_[TestType::VIEW_CMD_PARSER] = new ViewCmdParser();
    TestList.tests_[TestType::VIEW_CONSOLE_CONTROL] = new ViewConsoleControl();
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
