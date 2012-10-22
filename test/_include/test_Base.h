#ifndef TEST_BASE_H
#define TEST_BASE_H

enum class TestStatus {
    PASS,
    FAIL,
};

class Test {
public:
    virtual ~Test() {};
    virtual TestStatus run () = 0;
protected:
    Test() = default;
};

#endif//TEST_BASE_H
