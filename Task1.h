#pragma once

#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Задание 1: заменить минимальный по модулю элемент
     *        каждого столбца нулём
     */
    class Task1 : public Exercise {
    public:
        /**
         * @brief Конструктор
         * @param matrix ссылка на матрицу
         */
        explicit Task1(Matrix<int>& matrix);

        /**
         * @brief Выполнить задание
         */
        void solve() override;
    };

} // namespace miit::algebra
