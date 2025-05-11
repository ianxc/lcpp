#pragma once

#include <cassert>
#include <cctype>
#include <icecream.hpp>
#include <stack>
#include <string_view>
#include <type_traits>

namespace p224 {

template <typename T>
constexpr bool is_even(T x) {
    static_assert(std::is_integral_v<T>, "Integral T required");
    return !(x & 1);
}

class Solution {
  public:
    int calculate(std::string_view s) {
        std::stack<int> st;
        int expr_val = 0, curr_val = 0, curr_mul = 1;
        for (auto ch : s) {
            switch (ch) {
                case ' ':
                    continue;
                case '+':
                    expr_val += curr_val * curr_mul;
                    curr_val = 0;
                    curr_mul = 1;

                    IC(ch, expr_val, curr_val, curr_mul, st);
                    break;
                case '-':
                    expr_val += curr_val * curr_mul;
                    curr_val = 0;
                    curr_mul = -1;

                    IC(ch, expr_val, curr_val, curr_mul, st);
                    break;
                case '(':
                    st.push(expr_val);
                    st.push(curr_mul);
                    expr_val = 0;
                    assert(curr_val == 0);
                    curr_mul = 1;

                    IC(ch, expr_val, curr_val, curr_mul, st);
                    break;
                case ')': {
                    assert(!st.empty());
                    assert(is_even(st.size()));

                    // wrap up current expression
                    expr_val += curr_val * curr_mul;

                    // apply sign affecting whole parens expression.
                    curr_mul = st.top();
                    st.pop();
                    expr_val *= curr_mul;

                    // add previous running expression value to the
                    // parens-including-wrapping-sign expression.
                    auto old_expr_val = st.top();
                    st.pop();
                    expr_val = old_expr_val + expr_val;

                    // reset everything
                    curr_val = 0;
                    // not necessary to set `curr_mul = 1` as it will be set by
                    // the next +/-.

                    IC(ch, expr_val, curr_val, curr_mul, st);
                    break;
                }

                default:
                    assert(std::isdigit(ch));
                    int digit = ch - '0';
                    curr_val = 10 * curr_val + digit;

                    IC(ch, expr_val, curr_val, curr_mul, st);
                    break;
            }
        }

        expr_val += curr_val * curr_mul;
        return expr_val;
    }
};

}  // namespace p224
