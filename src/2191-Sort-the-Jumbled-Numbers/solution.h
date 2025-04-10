#pragma once

#include <algorithm>
#include <vector>

namespace p2191 {

class Solution {
  public:
    std::vector<int> sortJumbled(std::vector<int>& mapping,
                                 std::vector<int>& nums) {
        auto transform = [&mapping](int num) -> int {
            auto ans = 0;
            auto mult = 1;
            while (num != 0) {
                ans += mult * mapping[num % 10];
                mult *= 10;
                num /= 10;
            }
            return ans;
        };

        // copy nums to a new vector
        auto res{nums};
        std::sort(res.begin(), res.end(), [&transform](int a, int b) -> int {
            return transform(a) < transform(b);
        });
        return res;
    }
};

}  // namespace p2191
