#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <string_view>
#include <vector>

namespace p475 {

class Solution {
  public:
    int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
        std::ranges::sort(houses);
        std::ranges::sort(heaters);
        const auto A = static_cast<int>(houses.size());
        const auto H = static_cast<int>(heaters.size());
        // dump_vec("houses ", houses);
        // dump_vec("heaters", heaters);

        std::vector<int> min_dists(A, std::numeric_limits<int>().max());
        for (int a = 0, h = 0; a < A && h < H;) {
            if (houses[a] <= heaters[h]) {
                min_dists[a] = heaters[h] - houses[a];
                a++;
            } else {
                h++;
            }
        }

        // dump_vec("min_dists", min_dists);

        for (int a = A - 1, h = H - 1; a >= 0 && h >= 0;) {
            if (houses[a] > heaters[h]) {
                min_dists[a] = std::min(min_dists[a], houses[a] - heaters[h]);
                a--;
            } else {
                h--;
            }
        }

        // dump_vec("min_dists", min_dists);

        return *std::max_element(min_dists.begin(), min_dists.end());
    }

    template <typename T>
    void dump_vec(std::string_view s, std::vector<T>& xs) {
        std::cout << s << ' ';
        for (auto& x : xs) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
};

}  // namespace p475
