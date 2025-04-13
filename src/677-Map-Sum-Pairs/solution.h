#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace p677 {

template <typename T>
struct TrieNode {
    // not strictly necessary, but useful for debugging.
    char curr;

    // an associated value, if there is a search term terminating at this node.
    std::optional<T> value;

    // longer terms which include the current prefix.
    std::unordered_map<char, std::unique_ptr<TrieNode<T>>> children;

    TrieNode(char curr) : curr(curr), value(std::nullopt) {}

    TrieNode(char curr, T value) : curr(curr), value(value) {}
};

/*
Approaches:
1. Trie only, 1-pass insert, sum on read [chosen; worse time than others].
2. Trie only, 1-pass insert, backtrack + apply delta to intermediary nodes on
   insert.
3. Trie-only, 2-pass insert, 1 to get delta, 1 to insert + apply delta on
   insert.
4. Trie + Map. Map stores scores. Compute delta by looking up in map upon
   insert. Compute sum in O(K) time where K is the length of the string by
   walking forward without branching.
*/
class MapSum {
  private:
    std::unique_ptr<TrieNode<int>> root;

  public:
    MapSum() : root(std::make_unique<TrieNode<int>>('*')) {}

    void insert(const std::string& key, int val) {
        auto* curr_node = root.get();
        for (auto ch : key) {
            auto it = curr_node->children.find(ch);
            if (it == curr_node->children.end()) {
                auto [new_it, _] = curr_node->children.emplace(
                    ch, std::make_unique<TrieNode<int>>(ch));

                curr_node = new_it->second.get();
            } else {
                curr_node = it->second.get();
            }
        }
        curr_node->value = val;
    }

    int sum(const std::string& prefix) {
        auto* curr_node = root.get();
        for (auto ch : prefix) {
            auto it = curr_node->children.find(ch);
            if (it == curr_node->children.end()) {
                return 0;
            }
            auto* next_node = it->second.get();
            curr_node = next_node;
        }
        // curr_node has consumed the prefix. sum up all children recursively.
        return sum_rec(curr_node);
    }

    int sum_rec(const TrieNode<int>* node) {
        auto curr_sum = node->value.value_or(0);
        for (const auto& [_, child] : node->children) {
            curr_sum += sum_rec(child.get());
        }
        return curr_sum;
    }
};

}  // namespace p677
