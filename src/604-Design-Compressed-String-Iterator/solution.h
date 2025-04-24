#pragma once

#include <cassert>
#include <icecream.hpp>
#include <string>

namespace p604 {

int ctoi(char c) { return c - '0'; }

class StringIterator {
  private:
    size_t curr_idx;
    int curr_rem;
    std::string source_string;

  public:
    StringIterator(std::string compressedString) {
        this->source_string = std::move(compressedString);
        this->curr_idx = 0;
        if (this->source_string.length() >= 2) {
            auto first_rem = ctoi(this->source_string[1]);
            assert(first_rem > 0);
            this->curr_rem = first_rem;
        } else {
            this->curr_rem = 0;
        }
    }

    char next() {
        if (!this->hasNext()) {
            return ' ';
        }

        assert(this->curr_rem > 0);

        if (curr_rem == 1) {
            // prepare internal state to point to the next character
            auto to_return = this->source_string[this->curr_idx];
            this->curr_idx += 2;
            auto next_rem_idx = this->curr_idx + 1;
            this->curr_rem = next_rem_idx < this->source_string.length()
                                 ? ctoi(this->source_string[next_rem_idx])
                                 : 0;
            return to_return;
        }

        assert(this->curr_rem > 1);
        this->curr_rem--;
        return this->source_string[this->curr_idx];
    }

    bool hasNext() { return this->curr_idx < this->source_string.length(); }
};

}  // namespace p604
