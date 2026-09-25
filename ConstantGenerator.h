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
        /**
         * @brief Конструктор
         * @param value константное значение
         */
        ConstantGenerator(const int value = 0);

        /** @brief Возвращает константное значение */
        int generate() override;

        /** @brief Установить новое константное значение */
        void setValue(const int value);

        /** @brief Получить текущее константное значение */
        int getValue() const;
    };

} // namespace miit::algebra
