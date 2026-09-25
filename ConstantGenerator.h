#pragma once

#include "Generator.h"

namespace miit::algebra {

    /**
     * @brief Генератор, возвращающий константное значение
     */
    class ConstantGenerator : public Generator {
    private:
        int constantValue;

    public:
        ConstantGenerator(const int value = 0);

        int generate() override;
        void setValue(const int value);
        int getValue() const;
    };

} 
