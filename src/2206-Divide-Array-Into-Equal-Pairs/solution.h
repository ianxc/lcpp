#pragma once

#include <algorithm>
#include <vector>

namespace p2206 {

class Solution {
  public:
    bool divideArray(std::vector<int>& nums) {
        std::vector<bool> seen(501, false);
        for (auto n : nums) {
            seen[n] = !seen[n];
        }
        return std::find(seen.begin(), seen.end(), true) == seen.end();
    }
};

class WrongXorSolution {
  public:
    bool divideArray(std::vector<int>& nums) {
        auto xored_all = 0;
        for (auto n : nums) {
            xored_all ^= n;
        }
        return xored_all == 0;
    }
};

}  // namespace p2206
