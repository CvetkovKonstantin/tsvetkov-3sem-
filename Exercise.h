#pragma once

#include "Generator.h"
#include "Matrix.h"
#include <memory>
#include <string>

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс для упражнений
     *
     * Хранит матрицу и (при необходимости) генератор. Конкретное
     * задание реализуется в классе-наследнике.
     */
    class Exercise {
    protected:
        Matrix<int> matrix;
        std::unique_ptr<Generator> generator;

    public:
        Exercise() = default;
        virtual ~Exercise() = default;

        /** @brief Установить матрицу */
        void setMatrix(const Matrix<int>& mat);

        /** @brief Получить текущую матрицу */
        const Matrix<int>& getMatrix() const;

        /** @brief Установить генератор */
        void setGenerator(std::unique_ptr<Generator> gen);

        /** @brief Получить указатель на генератор */
        Generator* getGenerator() const;

        /** @brief Решение задачи (чисто виртуальный метод) */
        virtual void solve() = 0;

        /** @brief Описание задачи */
        virtual std::string getDescription() const = 0;
    };

} // namespace miit::algebra
