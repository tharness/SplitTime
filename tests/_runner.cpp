#include "_test.h"

std::vector<TestCase> tests;

int main() {
    int numTests = tests.size();
    int numFails = 0;
    std::cout << "\n" << "Running " << numTests << " tests:" << "\n\n";
    for (auto& test : tests) {
        auto success = test.test();
        if (success) {
            std::cout << "  PASS\t\t" << test.name << "\n";
        }
        else {
            std::cout << "########\n";
            std::cout << "# FAIL #\t" << test.name << "\n";
            std::cout << "########\n";
            ++numFails;
        }
    }
    std::cout << "\n";
    std::cout << "  Passed:\t" << numTests-numFails << "/" << numTests << "\n";
    if (numFails > 0) {
        std::cout << "\n";
        std::cout << "##############" << "\n";
        std::cout << "# Run Failed #\t" << numFails << "/" << numTests << "\n";
        std::cout << "##############" << "\n";
        std::cout << "\n";
    }
    else {
        std::cout << "\n";
        std::cout << "-- Run Passed -- " << "\n";
        std::cout << "\n";
    }
}