#include "solution.h"

#include <gtest/gtest.h>

using namespace p853;

namespace {

struct TestCase {
    int target;
    std::vector<int> position;
    std::vector<int> speed;
    int expected_fleets;
};

std::vector<TestCase> cases{
    {12, {10, 8, 0, 5, 3}, {2, 4, 1, 1, 3}, 3},
};

}  // namespace

TEST(test_suite_name, EasySolution3Passes) {
    EasySolution3Passes s;

    for (auto& [target, position, speed, expected_fleets] : cases) {
        EXPECT_EQ(s.carFleet(target, position, speed), expected_fleets);
    }
}

TEST(test_suite_name, EasySolution2Passes) {
    EasySolution2Passes s;

    for (auto& [target, position, speed, expected_fleets] : cases) {
        EXPECT_EQ(s.carFleet(target, position, speed), expected_fleets);
    }
}
