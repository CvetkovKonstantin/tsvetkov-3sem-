#include "Task2.h"
#include <cmath>
#include <vector>

namespace miit::algebra {

    Task2::Task2(Matrix<int>& matrix)
        : Exercise{ matrix }
    {
    }

    void Task2::solve()
    {
        if (matrix.isEmpty()) {
            return;
        }

        const std::size_t rows = matrix.getRows();

        const int maxAbs = findMaxAbs();
        const std::vector<int> lastRow = matrix[rows - 1];

        // Идём с конца, чтобы индексы не съезжали при вставке.
        for (std::size_t i = rows; i-- > 0;) {
            if (rowContainsValue(i, maxAbs)) {
                matrix.insertRow(i + 1, lastRow);
            }
        }
    }

    int Task2::findMaxAbs() const
    {
        const std::size_t rows = matrix.getRows();
        const std::size_t cols = matrix.getCols();

        int maxAbs = std::abs(matrix[0][0]);
        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                const int cur = std::abs(matrix[i][j]);
                if (cur > maxAbs) {
                    maxAbs = cur;
                }
            }
        }
        return maxAbs;
    }

    bool Task2::rowContainsValue(const std::size_t row, const int value) const
    {
        const std::size_t cols = matrix.getCols();
        for (std::size_t j = 0; j < cols; ++j) {
            if (std::abs(matrix[row][j]) == value) {
                return true;
            }
        }
        return false;
    }

} // namespace miit::algebra
