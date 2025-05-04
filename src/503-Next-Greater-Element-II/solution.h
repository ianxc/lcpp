#pragma once

#include <stack>
#include <vector>

namespace p503 {

class Solution {
  public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        const int n = nums.size();
        std::vector res(n, -1);
        std::stack<int> greater_to_find;
        for (int i = 0; i < 2 * n; i++) {
            while (!greater_to_find.empty() &&
                   nums[greater_to_find.top()] < nums[i % n]) {
                res[greater_to_find.top()] = nums[i % n];
                greater_to_find.pop();
            }
            // There's no need to add to the stack the second time around.
            // The second pass is just to discover next greater elements.
            if (i < n) greater_to_find.push(i);
        }
        return res;
    }
};

}  // namespace p503
