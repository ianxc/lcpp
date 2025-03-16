#pragma once

#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
  public:
    std::pair<int, int> two_sum(const std::vector<int>& nums, int target) {
        std::unordered_map<int, int> comps{};
        int n = nums.size();
        for (auto i = 0; i < n; i++) {
            auto it = comps.find(target - nums[i]);
            if (it != comps.end()) {
                return {it->second, i};
            };
            comps[nums[i]] = i;
        };
        return std::pair<int, int>{};
    }
};

class Solution2 {
  public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> comps{};
        int n = nums.size();
        for (auto i = 0; i < n; i++) {
            auto it = comps.find(target - nums[i]);
            if (it != comps.end()) {
                return {it->second, i};
            };
            comps[nums[i]] = i;
        };
        return {};
    }
};
