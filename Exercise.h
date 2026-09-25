#pragma once

#include "Generator.h"
#include "Matrix.h"
#include <memory>
#include <string>

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс для упражнений
     *
     * Хранит матрицу и (при необходимости) генератор.
     * Конкретное задание реализуется в классе-наследнике.
     */
    class Exercise {
    protected:
        Matrix<int> matrix;
        std::unique_ptr<Generator> generator;

    public:
        Exercise() = default;
        virtual ~Exercise() = default;

        void setMatrix(const Matrix<int>& mat);
        const Matrix<int>& getMatrix() const;

        void setGenerator(std::unique_ptr<Generator> gen);
        Generator* getGenerator() const;

        virtual void solve() = 0;
        virtual std::string getDescription() const = 0;
    };

} 
