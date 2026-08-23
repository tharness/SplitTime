#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>

struct TestCase {
    bool (*test)();
    std::string name;
    const char* file;
    int line;
};

extern std::vector<TestCase> tests;

struct TestRegistrar {
    TestRegistrar(bool (*test)(), const std::string& name,
                  const char* file, int line) {
        tests.push_back({test, name, file, line});
    }
};

#define TEST(name) \
    bool name(); \
    inline TestRegistrar register_##name(name, #name, __FILE__, __LINE__); \
    bool name()

#endif // TEST_H