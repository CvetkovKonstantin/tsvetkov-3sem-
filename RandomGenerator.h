#pragma once

#include "Generator.h"
#include <random>

namespace miit::algebra {

    /**
     * @brief Генератор случайных чисел в диапазоне [min, max]
     */
    class RandomGenerator : public Generator {
    private:
        mutable std::mt19937 generator;
        mutable std::uniform_int_distribution<int> distribution;

    public:
        /**
         * @brief Конструктор
         * @param min нижняя граница диапазона
         * @param max верхняя граница диапазона
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Сгенерировать случайное число
         * @return случайное число в диапазоне [min, max]
         */
        int generate() const override;
    };

} // namespace miit::algebra
