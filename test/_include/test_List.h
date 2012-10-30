#ifndef TEST_LIST_H
#define TEST_LIST_H

// Dependencies
#include <map>
#include <utility>

enum class TestType {
    SAMPLE_SUITE,

    // Basic Model Unit Tests
    MODEL_BASE_CONTROL,
    MODEL_LOGIC_CONTROL,

    // Algorithm Unit Tests
    ALG_CYCLE_DETECT,

    // User Interface Unit Tests
    VIEW_CONSOLE_CONTROL,
};

typedef std::pair<TestType, Test*> TestSuite;

class {
public:
    std::map<TestType, Test*> tests_;
} TestList;

#endif//TEST_LIST_H
