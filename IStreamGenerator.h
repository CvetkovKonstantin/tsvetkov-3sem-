#pragma once

#include "Generator.h"
#include <istream>

namespace miit::algebra {

    /**
     * @brief Генератор, считывающий значения из входного потока
     */
    class IStreamGenerator : public Generator {
    private:
        std::istream& in;

    public:
        /**
         * @brief Конструктор
         * @param in поток ввода
         */
        explicit IStreamGenerator(std::istream& in);

        /**
         * @brief Считать очередное значение из потока
         * @return считанное значение
         */
        int generate() const override;
    };

} // namespace miit::algebra
