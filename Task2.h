#pragma once

#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Задание 2: вставить после каждой строки, содержащей
     *        максимальный по модулю элемент, последнюю строку
     */
    class Task2 : public Exercise {
    public:
        /**
         * @brief Конструктор
         * @param matrix ссылка на матрицу
         */
        explicit Task2(Matrix<int>& matrix);

        /**
         * @brief Выполнить задание
         */
        void solve() override;

    private:
        /**
         * @brief Найти максимальный по модулю элемент во всей матрице
         * @return максимальное по модулю значение
         */
        int findMaxAbs() const;

        /**
         * @brief Проверить, содержит ли строка значение, совпадающее
         *        по модулю с заданным
         * @param row индекс строки
         * @param value искомое значение (по модулю)
         * @return true, если содержит
         */
        bool rowContainsValue(const std::size_t row, const int value) const;
    };

} // namespace miit::algebra
