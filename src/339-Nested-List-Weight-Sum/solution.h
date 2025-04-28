#pragma once

#include <cassert>
#include <vector>

namespace p339 {

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
  private:
    int val;
    std::vector<NestedInteger> nested;
    bool is_integer;

  public:
    // Constructor initializes an empty nested list.
    NestedInteger() : val(0), nested({}), is_integer(false) {};

    // Constructor initializes a single integer.
    NestedInteger(int value) : val(value), nested({}), is_integer(true) {};

    // Return true if this NestedInteger holds a single integer, rather than a
    // nested list.
    bool isInteger() const { return this->is_integer; }

    // Return the single integer that this NestedInteger holds, if it holds a
    // single integer. The result is undefined if this NestedInteger holds a
    // nested list
    int getInteger() const {
        assert(this->is_integer);
        return this->val;
    }

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value) {
        this->val = value;
        this->nested.clear();
        this->is_integer = true;
    };

    // Set this NestedInteger to hold a nested list and adds a nested integer to
    // it.
    void add(const NestedInteger &ni) {
        if (!this->is_integer) {
            this->val = 0;
            this->nested = {};
            this->is_integer = false;
        }
        this->nested.push_back(ni);
    }

    // Return the nested list that this NestedInteger holds, if it holds a
    // nested list. The result is undefined if this NestedInteger holds a single
    // integer
    const std::vector<NestedInteger> &getList() const {
        assert(!this->is_integer);
        return this->nested;
    }
};

// Essentially post-order DFS
class Solution {
  public:
    int depthSum(std::vector<NestedInteger> &nestedList) {
        auto sum_rec = [](const auto &self, int depth,
                          const NestedInteger &ni) -> int {
            if (ni.isInteger()) {
                return depth * ni.getInteger();
            }

            auto sum = 0;
            for (const auto &child_ni : ni.getList()) {
                sum += self(self, depth + 1, child_ni);
            }
            return sum;
        };

        auto sum = 0;
        for (auto &ni : nestedList) {
            sum += sum_rec(sum_rec, 1, ni);
        }
        return sum;
    }
};

}  // namespace p339
