#include "Task2.h"
#include <cmath>
#include <vector>

namespace miit::algebra {

    void Task2::solve() {
        if (matrix.isEmpty()) {
            return;
        }

        const size_t rows = matrix.getRows();
        const size_t cols = matrix.getCols();

        const int maxAbs = findMaxAbs();
        const std::vector<int> lastRow = matrix[rows - 1];

        std::vector<std::vector<int>> newData;
        newData.reserve(rows * 2);

        for (size_t i = 0; i < rows; ++i) {
            newData.push_back(matrix[i]);
            if (rowContainsValue(i, maxAbs)) {
                newData.push_back(lastRow);
            }
        }

        matrix.resize(newData.size(), cols);
        for (size_t i = 0; i < newData.size(); ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix[i][j] = newData[i][j];
            }
        }
    }

    std::string Task2::getDescription() const {
        return "Insert the last row after each row containing the maximum absolute value element";
    }

    int Task2::findMaxAbs() const {
        const size_t rows = matrix.getRows();
        const size_t cols = matrix.getCols();

        int maxAbs = std::abs(matrix[0][0]);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                const int cur = std::abs(matrix[i][j]);
                if (cur > maxAbs) {
                    maxAbs = cur;
                }
            }
        }
        return maxAbs;
    }

    bool Task2::rowContainsValue(const size_t row, const int value) const {
        const size_t cols = matrix.getCols();
        for (size_t j = 0; j < cols; ++j) {
            if (std::abs(matrix[row][j]) == value) {
                return true;
            }
        }
        return false;
    }

}
