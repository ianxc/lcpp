#pragma once

#include <icecream.hpp>
#include <vector>

namespace p370 {

class Solution {
  public:
    std::vector<int> getModifiedArray(int length,
                                      std::vector<std::vector<int>>& updates) {
        const int n = length + 1;
        std::vector<int> deltas(n);
        for (auto u : updates) {
            auto start = u[0], end_excl = u[1] + 1, incr = u[2];
            deltas[start] += incr;
            deltas[end_excl] -= incr;
        }
        for (int i = 1; i < n; i++) {
            deltas[i] += deltas[i - 1];
        }

        deltas.pop_back();
        return deltas;
    };
};

}  // namespace p370
