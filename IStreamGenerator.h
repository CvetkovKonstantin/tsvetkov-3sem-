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
        IStreamGenerator(std::istream& in = std::cin);
        int generate() override;
    };

} 
