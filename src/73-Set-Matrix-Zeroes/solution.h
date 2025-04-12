#pragma once

#include <algorithm>
#include <icecream.hpp>
#include <vector>

namespace p73 {

class TwoPassLinearSumSpaceSolution {
  public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        auto rows = static_cast<int>(matrix.size());
        auto cols = static_cast<int>(matrix.front().size());

        std::vector<bool> row_z(rows, false);
        std::vector<bool> col_z(cols, false);

        for (auto i = 0; i < rows; i++) {
            for (auto j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    row_z[i] = true;
                    col_z[j] = true;
                }
            }
        }

        for (auto i = 0; i < rows; i++) {
            for (auto j = 0; j < cols; j++) {
                if (row_z[i] || col_z[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

/*
input:
1, 1, 1, 0
1, 0, 1, 1
1, 1, 1, 1

exp output:
0, 0, 0, 0
0, 0, 0, 0
1, 0, 1, 0

Use left / top edge as marker
2, 2, 1, 0
2, 0, 1, 1
1, 1, 1, 1

Update excluding left/top edges.

Set 2 => 0 for left/top edges.

*/

class InPlaceSolution {
  private:
    struct first_has_zero {
        bool row;
        bool col;
    };

  public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        first_has_zero fhz{false, false};

        auto& first_row = matrix.front();
        auto rows = static_cast<int>(matrix.size());
        auto cols = static_cast<int>(first_row.size());

        // check if the first row and col have a zero.
        fhz.row = std::find(first_row.cbegin(), first_row.cend(), 0) !=
                  first_row.cend();
        for (int i = 0; !fhz.col && i < rows; i++) {
            fhz.col |= (matrix[i][0] == 0);
        }

        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (fhz.row) {
            std::fill(first_row.begin(), first_row.end(), 0);
        }
        if (fhz.col) {
            for (int i = 0; i < rows; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

}  // namespace p73
