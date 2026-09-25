#include "Task2.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace miit::algebra {

    void Task2::solve() {
        const size_t rows = matrix.getRows();
        const size_t cols = matrix.getCols();

        if (rows == 0 || cols == 0) {
            return; // нечего обрабатывать
        }

        // 1. Находим максимальный по модулю элемент во всей матрице
        const int maxAbsValue = findMaxAbs();

        // 2. Запоминаем последнюю строку (её будем вставлять)
        const std::vector<int> lastRow = matrix[rows - 1];

        // 3. Строим новую матрицу, вставляя lastRow после нужных строк
        std::vector<std::vector<int>> newData;
        newData.reserve(rows * 2);

        for (size_t i = 0; i < rows; ++i) {
            newData.push_back(matrix[i]);              // исходная строка
            if (rowContainsValue(i, maxAbsValue)) {
                newData.push_back(lastRow);            // вставка после неё
            }
        }

        // 4. Переносим данные обратно в matrix
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
                const int curAbs = std::abs(matrix[i][j]);
                if (curAbs > maxAbs) {
                    maxAbs = curAbs;
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
