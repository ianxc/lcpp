#pragma once

#include <array>
#include <queue>
#include <vector>

namespace p542 {

class Solution {
  private:
    using vec2d = std::pair<int, int>;

    static constexpr std::array<vec2d, 4> offsets{
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};

  public:
    std::vector<std::vector<int>> updateMatrix(
        std::vector<std::vector<int>>& mat) {
        const int m = mat.size();
        const int n = mat.front().size();

        std::vector<std::vector<int>> res(m, std::vector(n, 0));

        std::queue<vec2d> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        auto curr_level = 0;
        while (!q.empty()) {
            curr_level++;
            const int level_size = q.size();
            for (int c = 0; c < level_size; c++) {
                auto [i, j] = q.front();
                q.pop();
                for (const auto& [di, dj] : offsets) {
                    auto ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                        mat[ni][nj] != 0) {
                        q.push({ni, nj});
                        mat[ni][nj] = 0;
                        res[ni][nj] = curr_level;
                    }
                }
            }
        }
        return res;
    };
};

}  // namespace p542
