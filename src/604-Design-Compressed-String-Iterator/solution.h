#pragma once

#include <cassert>
#include <cctype>
#include <icecream.hpp>
#include <string>

namespace p604 {

int ctoi(char c) { return c - '0'; }

class StringIterator {
  private:
    std::string source_string;
    char curr_char;
    int curr_rem;
    size_t next_char_idx;

  public:
    StringIterator(std::string compressedString) {
        this->curr_char = compressedString[0];

        this->curr_rem = 0;
        auto curr_rem_idx = 1u;
        while (curr_rem_idx < compressedString.length() &&
               std::isdigit(compressedString[curr_rem_idx])) {
            this->curr_rem *= 10;
            this->curr_rem += ctoi(compressedString[curr_rem_idx]);
            curr_rem_idx++;
        }
        this->next_char_idx = curr_rem_idx;

        this->source_string = std::move(compressedString);
    }

    char next() {
        if (!this->hasNext()) {
            return ' ';
        }
        if (curr_rem == 1) {
            // prepare internal state to point to the next character
            auto to_return = curr_char;
            this->curr_char = this->source_string[this->next_char_idx];
            this->curr_rem = 0;
            auto curr_rem_idx = this->next_char_idx + 1;
            while (curr_rem_idx < this->source_string.length() &&
                   std::isdigit(this->source_string[curr_rem_idx])) {
                this->curr_rem *= 10;
                this->curr_rem += ctoi(this->source_string[curr_rem_idx]);
                curr_rem_idx++;
            }
            this->next_char_idx = curr_rem_idx;

            return to_return;
        }

        assert(this->curr_rem > 1);
        this->curr_rem--;
        return this->curr_char;
    }

    bool hasNext() { return this->curr_rem > 0; }
};

}  // namespace p604
