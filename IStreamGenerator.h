#pragma once

#include "Generator.h"
#include <iostream>

namespace miit::algebra {

    /**
     * @brief Генератор, считывающий значения из потока ввода
     */
    class IStreamGenerator : public Generator {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор
         * @param in поток ввода (по умолчанию std::cin)
         */
        IStreamGenerator(std::istream& in = std::cin);

        /** @brief Считать очередное значение */
        int generate() override;
    };

} // namespace miit::algebra
