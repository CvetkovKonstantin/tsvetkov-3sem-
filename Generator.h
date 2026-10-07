#pragma once

namespace miit::algebra {

    /**
     * @brief Абстрактный генератор целочисленных значений
     *
     * Базовый класс для всех способов заполнения матрицы: случайными
     * числами, значениями из потока ввода и константой.
     */
    class Generator {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Generator() = default;

        /**
         * @brief Сгенерировать очередное значение
         * @return сгенерированное значение
         */
        virtual int generate() const = 0;
    };

} // namespace miit::algebra
