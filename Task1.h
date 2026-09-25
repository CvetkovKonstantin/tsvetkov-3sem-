#pragma once

#include "Exercise.h"
#include <string>

namespace miit::algebra {

    /**
     * @brief Задание 1: заменить минимальный по модулю элемент
     *        каждого столбца нулём.
     */
    class Task1 : public Exercise {
    public:
        Task1() = default;

        void solve() override;
        std::string getDescription() const override;

    private:
        size_t findMinAbsInColumn(const size_t col) const;
        void checkMatrixNotEmpty() const;
    };

}
