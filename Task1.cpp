#include "Task1.h"
#include <cmath>

namespace miit::algebra {

    Task1::Task1(Matrix<int>& matrix)
        : Exercise{ matrix }
    {
    }

    void Task1::solve()
    {
        if (matrix.isEmpty()) {
            return;
        }

        const std::size_t rows = matrix.getRows();
        const std::size_t cols = matrix.getCols();

        for (std::size_t j = 0; j < cols; ++j) {
            std::size_t minRow = 0;
            int minAbs = std::abs(matrix[0][j]);

            for (std::size_t i = 1; i < rows; ++i) {
                const int curAbs = std::abs(matrix[i][j]);
                if (curAbs < minAbs) {
                    minAbs = curAbs;
                    minRow = i;
                }
            }
            matrix[minRow][j] = 0;
        }
    }

} // namespace miit::algebra
