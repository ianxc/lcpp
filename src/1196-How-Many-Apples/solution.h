#pragma once

#include <bits/stdc++.h>

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
