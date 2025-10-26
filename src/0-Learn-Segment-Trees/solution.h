#pragma once

#include <algorithm>
#include <vector>

namespace p0_learn_segment_trees {

class SumSegmentTree {
  private:
    size_t _size;
    std::vector<int> tree;

    void _build(const std::vector<int>& input, size_t curr_idx, size_t left_idx,
                size_t right_idx) {
        if (left_idx == right_idx) {
            tree[curr_idx] = input[left_idx];
        } else {
            auto mid_idx = left_idx + (right_idx - left_idx) / 2;
            _build(input, curr_idx * 2, left_idx, mid_idx);
            _build(input, curr_idx * 2 + 1, mid_idx + 1, right_idx);
            tree[curr_idx] = tree[curr_idx * 2] + tree[curr_idx * 2 + 1];
        }
    }

    int _sum(size_t curr_idx, size_t left_idx, size_t right_idx,
             size_t left_desired, size_t right_desired) {
        if (left_desired > right_desired) {
            return 0;
        }
        if (left_desired == left_idx && right_desired == right_idx) {
            return this->tree[curr_idx];
        }
        // mid_idx defines the cutoff between the left and right child's ranges.
        auto mid_idx = left_idx + (right_idx - left_idx) / 2;

        // Take the min to clip the right boundary of the left query to not
        // exceed the left child's range.
        auto left_sum = _sum(curr_idx * 2, left_idx, mid_idx, left_desired,
                             std::min(right_desired, mid_idx));
        // Similarly, take the max to clip the left boundary of the right query
        // to precede the right child's range.
        auto right_sum =
            _sum(curr_idx * 2 + 1, mid_idx + 1, right_idx,
                 std::max(left_desired, mid_idx + 1), right_desired);
        return left_sum + right_sum;
    }

  public:
    SumSegmentTree(const std::vector<int>& input) {
        this->tree = {};
        this->tree.reserve(4 * input.size());
        this->_size = input.size();
        this->_build(input, 1, 0, input.size() - 1);
    };

    int size() { return this->_size; }

    int sum(size_t left_idx, size_t right_idx) {
        // WIP
        return -1;
    }
};

}  // namespace p0_learn_segment_trees
