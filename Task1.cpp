#include "Task1.h"
#include <cmath>
#include <stdexcept>

namespace miit::algebra {

    void Task1::solve() {
        checkMatrixNotEmpty();

        const size_t cols = matrix.getCols();
        for (size_t j = 0; j < cols; ++j) {
            const size_t minRow = findMinAbsInColumn(j);
            matrix[minRow][j] = 0;
        }
    }

    std::string Task1::getDescription() const {
        return "Replace the minimum absolute value element of each column with zero";
    }

    size_t Task1::findMinAbsInColumn(const size_t col) const {
        checkMatrixNotEmpty();

        const size_t rows = matrix.getRows();
        if (col >= matrix.getCols()) {
            throw std::out_of_range("Column index out of range: " + std::to_string(col));
        }

        size_t minRow = 0;
        int minValue = std::abs(matrix[0][col]);

        for (size_t i = 1; i < rows; ++i) {
            const int absValue = std::abs(matrix[i][col]);
            if (absValue < minValue) {
                minValue = absValue;
                minRow = i;
            }
        }
        return minRow;
    }

    void Task1::checkMatrixNotEmpty() const {
        if (matrix.getRows() == 0 || matrix.getCols() == 0) {
            throw std::runtime_error("Matrix is empty. Cannot perform operation.");
        }
    }

}
