#pragma once

#include <algorithm>
#include <tuple>
#include <vector>

namespace p0_max_num_overlapping_intervals {

class Solution {
  private:
    enum PointKind : bool { end, start };

    struct PairCmp {
        template <typename T, typename U>
        bool operator()(std::pair<T, U> lhs, std::pair<T, U> rhs) {
            return std::tie(lhs.first, lhs.second) <
                   std::tie(rhs.first, rhs.second);
        }
    };

  public:
    int max_num_overlapping_intervals(
        std::vector<std::pair<int, int>>& intervals) {
        std::vector<std::pair<int, PointKind>> to_sweep;
        to_sweep.reserve(intervals.size() * 2);

        for (auto [start, end] : intervals) {
            to_sweep.emplace_back(start, PointKind::start);
            to_sweep.emplace_back(end, PointKind::end);
        }

        std::sort(to_sweep.begin(), to_sweep.end(), PairCmp{});

        auto max_overlapping = 0;
        auto curr_overlapping = 0;
        for (auto [v, k] : to_sweep) {
            if (k == PointKind::start) {
                curr_overlapping++;
                max_overlapping = std::max(max_overlapping, curr_overlapping);
            } else {
                curr_overlapping--;
            }
        }
        return max_overlapping;
    }
};

}  // namespace p0_max_num_overlapping_intervals
