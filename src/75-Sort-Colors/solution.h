#pragma once

#include <icecream.hpp>
#include <utility>
#include <vector>

namespace p75 {

/*
Useful comments:
https://leetcode.com/problems/sort-colors/editorial/comments/260760/
https://leetcode.com/problems/sort-colors/editorial/comments/1144711/?parent=260760

*/
class Solution {
  public:
    void sortColors(std::vector<int>& nums) {
        IC_CONFIG.output(std::cout);

        const auto n = static_cast<int>(nums.size());
        int left = 0, curr = 0, right = n - 1;

        while (curr <= right) {
            IC(left, curr, right, nums);
            if (nums[curr] == 0) {
                std::swap(nums[left], nums[curr]);
                left++;
                curr++;
            } else if (nums[curr] == 2) {
                std::swap(nums[curr], nums[right]);
                right--;
            } else {
                curr++;
            }
        }
    }
};

}  // namespace p75
