#pragma once

#include "Matrix.h"

namespace miit::algebra {

    /**
     * @brief Базовый класс для заданий над матрицей
     *
     * Хранит ссылку на матрицу и предоставляет чисто виртуальный
     * метод solve() для выполнения конкретного задания.
     */
    class Exercise {
    protected:
        Matrix<int>& matrix;

    public:
        /**
         * @brief Конструктор
         * @param matrix ссылка на матрицу
         */
        explicit Exercise(Matrix<int>& matrix);

        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Exercise() = default;

        /**
         * @brief Решить задание
         */
        virtual void solve() = 0;
    };

} // namespace miit::algebra
