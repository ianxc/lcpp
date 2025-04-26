#pragma once

#include <cassert>
#include <string_view>

namespace p1616 {

class Solution {
  private:
    bool is_substr_palindrome(std::string_view s, int i, int j) {
        while (i < j && s[i] == s[j]) {
            i++;
            j--;
        }
        return i >= j;
    }

    std::pair<int, int> advance_while_palindrome(std::string_view prefix_str,
                                                 std::string_view suffix_str) {
        auto i = 0, j = static_cast<int>(suffix_str.length() - 1);
        while (i < j && prefix_str[i] == suffix_str[j]) {
            i++;
            j--;
        }
        return {i, j};
    }

    bool are_appended_palindromes(std::string_view prefix_str,
                                  std::string_view suffix_str) {
        auto [i, j] = advance_while_palindrome(prefix_str, suffix_str);
        return is_substr_palindrome(prefix_str, i, j);
    }

  public:
    bool checkPalindromeFormation(std::string_view a, std::string_view b) {
        assert(a.length() == b.length());
        return are_appended_palindromes(a, b) || are_appended_palindromes(b, a);
    }
};

}  // namespace p1616
