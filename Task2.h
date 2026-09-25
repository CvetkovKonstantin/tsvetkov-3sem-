#pragma once

#include "Exercise.h"
#include <string>

namespace miit::algebra {

    /**
     * @brief Задание 2: удалить все столбцы, в которых первый элемент
     *        больше последнего.
     */
    class Task2 : public Exercise {
    public:
        Task2() = default;

        void solve() override;
        std::string getDescription() const override;
    };

} // namespace miit::algebra
