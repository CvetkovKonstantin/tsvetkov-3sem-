#pragma once

#include "Exercise.h"
#include <string>

namespace miit::algebra {

    /**
     * @brief Задание 1: заменить минимальный по модулю элемент
     *        каждого столбца нулём.
     */
    class Task1 : public Exercise {
    public:
        Task1() = default;

        void solve() override;
        std::string getDescription() const override;

    private:
        /** @brief Найти индекс строки с минимальным по модулю элементом */
        size_t findMinAbsInColumn(const size_t col) const;

        /** @brief Проверить, что матрица не пустая */
        void checkMatrixNotEmpty() const;
    };

} // namespace miit::algebra
