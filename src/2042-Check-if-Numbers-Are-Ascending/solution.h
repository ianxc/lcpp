#pragma once

#include <cctype>
#include <icecream.hpp>
#include <string>

class Solution {
  public:
    bool areNumbersAscending(std::string s) {
        IC_CONFIG.output(std::cout);

        int length = s.size();
        auto last_num = -1, curr_num = 0, i = 0;
        auto curr_is_digit = false;
        while (i < length) {
            IC(i, s[i]);
            if (s[i] == ' ') {
                IC_CONFIG_SCOPE();
                IC_CONFIG.prefix("got_space");
                IC(i, s[i], curr_num, last_num, curr_is_digit);
                // reset everything
                if (curr_is_digit) {
                    if (last_num >= curr_num) {
                        return false;
                    }
                    last_num = curr_num;
                    curr_num = 0;
                    curr_is_digit = false;
                }

                i++;
                continue;
            }
            IC(i, s[i], curr_is_digit);
            if (!curr_is_digit && (std::isdigit(s[i]) != 0)) {
                IC_CONFIG_SCOPE();
                IC_CONFIG.prefix("set_is_digit");
                IC(i, s[i]);
                curr_is_digit = true;
            }

            if (curr_is_digit) {
                curr_num = curr_num * 10 + (s[i] - '0');
            }
            IC(i, s[i], curr_num, last_num);
            i++;
        };

        // need this when the last token is anumber
        return !curr_is_digit || last_num < curr_num;
    }
};
