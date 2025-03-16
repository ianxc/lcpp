#pragma once

#include <algorithm>
#include <vector>

#include "icecream.hpp"

class Solution {
  public:
    std::vector<int> sortJumbled(std::vector<int>& mapping,
                                 std::vector<int>& nums) {
        auto transform = [&mapping](int num) -> int {
            auto ans = 0;
            auto mult = 1;
            while (num != 0) {
                IC(num % 10, mapping[num % 10]);
                ans += mult * mapping[num % 10];
                mult *= 10;
                num /= 10;
                IC(ans, mult, num);
            }
            return ans;
        };

        auto res = std::vector(nums);
        std::sort(res.begin(), res.end(), [&transform](int a, int b) -> int {
            return transform(a) < transform(b);
        });
        return res;
    }
};
