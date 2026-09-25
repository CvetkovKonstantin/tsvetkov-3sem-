#pragma once

namespace miit::algebra {

    /**
     * @brief Абстрактный генератор целочисленных значений
     *
     * Базовый класс для всех способов заполнения матрицы. Конкретный
     * алгоритм реализуется в классе-наследнике.
     */
    class Generator {
    public:
        virtual ~Generator() = 0;
        virtual int generate() = 0;
    };

    inline Generator::~Generator() {}

} 
