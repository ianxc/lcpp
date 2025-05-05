#include "solution.h"

#include <gtest/gtest.h>

using namespace p224;

namespace {

// use an STL type for built-in pretty-printing.
using TestCase = std::pair<std::string, int>;

const std::vector<TestCase> cases{
    {"1 + 1", 2},
    {"2-1 + 2 ", 3},
    {"(1+(4+5+2)-3)+(6+8)", 23},
};

class CalculatorTest : public ::testing::TestWithParam<TestCase> {};

INSTANTIATE_TEST_SUITE_P(CalculatorCases, CalculatorTest,
                         ::testing::ValuesIn(cases));

TEST_P(CalculatorTest, CalculateExpression) {
    Solution s;

    const auto& [input, expected] = CalculatorTest::GetParam();

    EXPECT_EQ(s.calculate(input), expected);
}

}  // namespace
