#pragma once

#include <icecream.hpp>
#include <string>

namespace p1784 {

class Solution {
  public:
    bool checkOnesSegment(std::string s) {
        auto seen_lsb_one = false;
        for (auto i = static_cast<const int>(s.size()); i >= 0; i--) {
            switch (s[i]) {
                case '1':
                    seen_lsb_one = true;
                    break;
                case '0':
                    if (seen_lsb_one) return false;
                    break;
            }
        }
        return true;
    }
};

class EasySolution {
  public:
    bool checkOnesSegment(const std::string& s) {
        return s.find("01") == std::string::npos;
    }
};

}  // namespace p1784
