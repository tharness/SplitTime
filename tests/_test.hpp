#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <vector>

struct TestCase {
    bool (*test)(); 
    std::string name;
};

extern std::vector<TestCase> tests;

struct TestRegistrar {
    TestRegistrar(bool (*test)(), const std::string& name) {
        tests.push_back({test, name});
    }
};

#define TEST(name) \
    bool name(); \
    inline TestRegistrar register_##name(name, #name); \
    bool name() 

#endif // TEST_HPP