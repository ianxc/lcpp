#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

namespace p2233 {
/*
==Intuition==

Given a fixed perimeter (think "amount of resources"), area (product of 2
numbers) is maximised when we have a square.

Similarly, for cube volume and edge length.

Similarly, for this problem, the elements of `nums` are the edge lengths and the
max product we want is the "area".

Our fixed amount of resources is `sum(nums) + k`.

Since we're not decrementing any numbers, we should increase the smallest number
at each step to maximise the product.

==Implementation==

Standard:
1. min-heapify `nums`. If using std::vector, this means the smallest numbers
should go to the end.
2. get the min, poll, increment, offer back, maintain heap invariant.
3. do this k times.
4. compute product.

Optimization: suppose m = min(nums). any n >= m+k will definitely never be the
minimum, so we can partition `nums` in place to have n >= m+k in the front of
the vector, and heapify only the end of the vector.

*/
class Solution {
  public:
    int maximumProduct(std::vector<int>& nums, int k) {
        int m = *std::min_element(nums.begin(), nums.end());
        auto heap_end =
            std::partition(nums.begin(), nums.end(),
                           [m, k](auto n) -> bool { return n < m + k; });

        // want a min heap, therefore use a > b i.e. std::greater<>{}.
        auto cmp = std::greater<>{};
        std::make_heap(nums.begin(), heap_end, cmp);

        for (int i = 0; i < k; i++) {
            std::pop_heap(nums.begin(), heap_end, cmp);
            // ++ has a higher precendence than *.
            (*std::prev(heap_end))++;
            std::push_heap(nums.begin(), heap_end, cmp);
        }

        constexpr long MOD = 1e9 + 7;
        auto res = std::accumulate(
            nums.begin(), nums.end(), 1L,
            [](long acc, int n) -> long { return (acc * n) % MOD; });

        return static_cast<int>(res);
    }
};

}  // namespace p2233
