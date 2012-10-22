#ifndef TEST_LIST_H
#define TEST_LIST_H

// Dependencies
#include <map>
#include <utility>

enum class TestType {
    MODEL_BASE_CONTROL,
};

typedef std::pair<TestType, Test*> TestSuite;

class {
public:
    std::map<TestType, Test*> tests_;
} TestList;

#endif//TEST_LIST_H
