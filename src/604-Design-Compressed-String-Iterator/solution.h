#pragma once

#include <cassert>
#include <icecream.hpp>
#include <string>
#include <string_view>

namespace p604 {

int ctoi(char c) { return c - '0'; }

class StringIterator {
  private:
    std::string source_string;
    char curr_char;
    int curr_rem;
    size_t next_char_idx;

    struct compute_rem_t {
        int curr_rem;
        size_t next_char_idx;
    };

    static compute_rem_t compute_rem(const std::string_view source,
                                     size_t start_rem_idx) {
        auto curr_rem = 0;
        auto curr_rem_idx = start_rem_idx;
        while (curr_rem_idx < source.length() &&
               std::isdigit(source[curr_rem_idx])) {
            curr_rem *= 10;
            curr_rem += ctoi(source[curr_rem_idx]);
            curr_rem_idx++;
        }
        return {curr_rem, curr_rem_idx};
    }

  public:
    StringIterator(std::string compressedString) {
        this->source_string = std::move(compressedString);
        this->curr_char = this->source_string[0];

        auto computed_rem = compute_rem(this->source_string, 1);
        this->curr_rem = computed_rem.curr_rem;
        this->next_char_idx = computed_rem.next_char_idx;
    }

    char next() {
        if (!this->hasNext()) {
            return ' ';
        }
        if (curr_rem == 1) {
            // prepare internal state to point to the next character
            auto to_return = curr_char;
            this->curr_char = this->source_string[this->next_char_idx];

            auto computed_rem =
                compute_rem(this->source_string, this->next_char_idx + 1);
            this->curr_rem = computed_rem.curr_rem;
            this->next_char_idx = computed_rem.next_char_idx;

            return to_return;
        }

        assert(this->curr_rem > 1);
        this->curr_rem--;
        return this->curr_char;
    }

    bool hasNext() { return this->curr_rem > 0; }
};

}  // namespace p604
