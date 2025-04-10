#include <icecream.hpp>
#include <iostream>
#include <unordered_map>

#include "solution.h"

using namespace p0_build_demo;

int main() {
    std::cout << "Hello, world!\n";
    std::cout << "4 # 5 = " << add_double_2nd(4, 5) << '\n';
    auto x = 12;
    std::cout << x << '\n';
    std::unordered_map<int, int> m;
    m[2] = 3;
    m[3] = 10;
    std::cout << "m.size() = " << m.size() << '\n';
    IC(m);
    return 0;
}
