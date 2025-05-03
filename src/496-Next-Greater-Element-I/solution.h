#pragma once

#include <unordered_map>
#include <vector>

namespace p496 {

class Solution {
  public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1,
                                        std::vector<int>& nums2) {
        // index_map usage only works when nums1 and nums2 elements are unique
        // (they are specified to be unique).
        std::unordered_map<int, int> index_map;
        index_map.reserve(nums1.size());
        for (int i = 0; i < static_cast<const int>(nums1.size()); i++) {
            index_map[nums1[i]] = i;
        }

        std::vector<int> next_greater(nums1.size(), -1);
        std::vector<int> seen_values;
        for (int i = 0; i < static_cast<const int>(nums2.size()); i++) {
            int seen_value;
            while (!seen_values.empty() &&
                   (seen_value = seen_values.back()) < nums2[i]) {
                seen_values.pop_back();
                auto index_to_update = index_map.find(seen_value);
                if (index_to_update != index_map.end()) {
                    next_greater[index_to_update->second] = nums2[i];
                }
            }
            seen_values.emplace_back(nums2[i]);
        }

        return next_greater;
    }
};

}  // namespace p496
