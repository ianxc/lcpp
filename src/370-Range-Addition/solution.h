#pragma once

#include <icecream.hpp>
#include <vector>

namespace p370 {

class Solution {
  public:
    std::vector<int> getModifiedArray(int length,
                                      std::vector<std::vector<int>>& updates) {
        std::vector<int> deltas(length);
        for (auto u : updates) {
            auto start = u[0], end_excl = u[1] + 1, incr = u[2];
            deltas[start] += incr;
            if (end_excl < length) {
                deltas[end_excl] -= incr;
            }
        }

        for (int i = 1; i < length; i++) {
            deltas[i] += deltas[i - 1];
        }

        return deltas;
    };
};

}  // namespace p370
