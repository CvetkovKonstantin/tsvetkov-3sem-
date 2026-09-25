#pragma once

#include "Exercise.h"
#include <string>

namespace miit::algebra {

    /**
     * @brief Задание 2: вставить после каждой строки, содержащей
     *        максимальный по модулю элемент, последнюю строку.
     */
    class Task2 : public Exercise {
    public:
        Task2() = default;

        void solve() override;
        std::string getDescription() const override;

    private:
        int findMaxAbs() const;
        bool rowContainsValue(const size_t row, const int value) const;
    };

} 
