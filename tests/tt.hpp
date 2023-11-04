#include <iostream>
#include <vector>
#include <functional>
#include <string>


/**
    void testX() {
        int x{};
        test::test("X equals 0", [&]() {
            test::pray(x == 0);
        });
    }
    std::vector allTests {
        testPseudoLegalMoveGeneration,
        testSanity
    };

    test::executeAll(allTests);
*/

namespace tt {

int pray_index = 0;
struct TestCase {
    std::string description;
    std::function<void()> func;
};
std::vector<TestCase> testCases;

class MyFault : public std::exception {
    public:
        MyFault() = default;
};

void pray(bool cond) {
    ++pray_index;
    if(!cond) throw MyFault();
}


template <typename Func>
void test(const std::string& description, Func&& func) {
    testCases.emplace_back(description, func);
}

template <typename Func>
void executeAll(Func&& allTests) {
    std::cout << "Starting tests...\n\n";
    int total_tests = 0;
    int errors = 0;
    for(const auto& test : allTests) {
        // for each test category, populate testCases with its specific test cases
        test();
        for(const auto& test_case : testCases) {
            bool err_found = false;
            if(test_case.description != "") {
                std::cout << "[Test Case: \"" << test_case.description << "\"] ";
            }
            try {
                test_case.func();
            } catch (MyFault& err) {
                std::cout << " ❌" << "  Prayer #" << pray_index << " failed\n";
                ++errors;
                err_found = true;
            };
            if(!err_found) {
                std::cout << "✅\n";
            }
            pray_index = 0;
        }
        ++total_tests;
        // empty the test cases vector for the next test category
        testCases.clear();
        std::cout << "\n";
    };

    if(errors == 0 || total_tests == 0) {
        std::cout << "🎉🎉🎉 All tests cleared! 🎉🎉🎉\n";
    } else {
        std::cout << 100.0*(total_tests-errors)/total_tests << "% of tests cleared.\n";
    }
}

}