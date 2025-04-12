#pragma once

#include <cctype>
#include <icecream.hpp>
#include <string>

namespace p408 {

class Solution {
  public:
    bool validWordAbbreviation(std::string word, std::string abbr) {
        int i = 0, j = 0, wn = word.size(), an = abbr.size();
        int curr_num = 0;
        while (i < wn && j < an) {
            if (std::isdigit(abbr[j]) != 0) {
                auto digit = abbr[j] - '0';
                // reject leading zeros
                if (digit == 0 && curr_num == 0) {
                    return false;
                }
                curr_num = curr_num * 10 + (abbr[j] - '0');
                j++;
                continue;
            }

            // at this point, j should be pointing at the start of a letter run.
            i += curr_num;
            curr_num = 0;
            if (i >= wn) {
                // the abbreviation requires too many letters, so we've gone
                // beyond the word's length.
                return false;
            }

            // we have aligned i and j to the first post-number-jump letter
            if (word[i] != abbr[j]) {
                return false;
            }

            i++;
            j++;
        }
        IC(i, word[i], j, abbr[j], curr_num);
        // don't forget substitution numbers at the ends! we
        // need to advance the word by this number of chars.
        i += curr_num;
        return i == wn && j == an;
    }
};

}  // namespace p408
