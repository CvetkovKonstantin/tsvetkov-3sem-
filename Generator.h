#pragma once

namespace miit::algebra {

    /**
     * @brief Абстрактный генератор целочисленных значений
     *
     * Базовый класс для всех способов заполнения матрицы: случайными
     * числами, вводом из потока и константой.
     */
    class Generator {
    public:
        virtual ~Generator() = 0;
        virtual int generate() = 0;
    };

    inline Generator::~Generator() {}

} // namespace miit::algebra
