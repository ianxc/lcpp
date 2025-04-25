#pragma once

#include <algorithm>
#include <vector>

namespace p853 {

class EasySolution3Passes {
  public:
    int carFleet(int target, std::vector<int>& position,
                 std::vector<int>& speed) {
        const auto n = position.size();
        std::vector<std::pair<int, int>> rem_dists;
        rem_dists.reserve(n);

        for (auto i = 0u; i < n; i++) {
            rem_dists.emplace_back(target - position[i], speed[i]);
        }

        std::sort(rem_dists.begin(), rem_dists.end(),
                  [](auto p1, auto p2) -> bool { return p1.first < p2.first; });

        std::vector<double> times;
        times.reserve(n);
        for (auto i = 0u; i < n; i++) {
            times.emplace_back(double(rem_dists[i].first) /
                               rem_dists[i].second);
        }

        // dump_vec("times", times);

        auto fleet_max_time = times[0];
        auto fleet_count = 1;
        for (auto i = 1u; i < n; i++) {
            if (times[i] > fleet_max_time) {
                // start a new fleet as the i-th car cannot catch up to the
                // existing fleet.
                fleet_max_time = times[i];
                fleet_count++;
            }
        }
        return fleet_count;
    }
};

class EasySolution2Passes {
  public:
    int carFleet(int target, std::vector<int>& position,
                 std::vector<int>& speed) {
        const auto n = position.size();
        std::vector<std::pair<int, double>> rem_times(n);
        for (auto i = 0u; i < n; i++) {
            rem_times[i] = {position[i],
                            double(target - position[i]) / speed[i]};
        }
        auto cmp = [](auto p1, auto p2) -> bool { return p1.first > p2.first; };
        std::sort(rem_times.begin(), rem_times.end(), cmp);

        // alt:
        // https://leetcode.com/problems/car-fleet/solutions/476982/c-97-o-nlogn-o-n-position-arrival-time-sort/comments/933949/
        auto fleet_max_time = rem_times[0].second;
        auto fleet_count = 1;
        for (auto i = 1u; i < n; i++) {
            if (rem_times[i].second > fleet_max_time) {
                fleet_max_time = rem_times[i].second;
                fleet_count++;
            }
        }
        return fleet_count;
    }
};

}  // namespace p853
