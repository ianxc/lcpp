#pragma once

#include <algorithm>
#include <icecream.hpp>
#include <vector>

class Solution {
  public:
    int maxNumberOfApples(std::vector<int>& weight) {
        std::sort(weight.begin(), weight.end());
        const auto n = static_cast<int>(weight.size());
        auto sum = 0;
        for (auto i = 0; i < n; i++) {
            sum += weight[i];
            if (sum > 5000) {
                return i;
            }
        }
        return n;
    }
};

class HeapSolution {
  public:
    int maxNumberOfApples(std::vector<int>& weight) {
        // stl defaults to max-heap (python + java default to min-heap).
        // want a min-heap here, so create a comparator and use it consistently.
        auto cmp = [](int a, int b) -> bool { return a > b; };
        std::make_heap(weight.begin(), weight.end(), cmp);

        int n = weight.size();
        int sum = 0;
        for (auto i = 0; i < n; i++) {
            sum += weight.front();
            if (sum > 5000) return i;
            std::pop_heap(weight.begin(), weight.end(), cmp);
            weight.pop_back();
        }
        return n;
    }
};
