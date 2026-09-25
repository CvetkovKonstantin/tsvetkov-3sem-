#pragma once

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

namespace miit::algebra {

    /**
     * @brief Шаблонный класс матрицы (двумерного массива)
     * @tparam T тип элементов матрицы
     *
     * Класс не зависит от конкретных потоков ввода-вывода и не знает
     * ничего о задачах и генераторах — это чистый контейнер.
     */
    template <typename T>
    class Matrix {
    private:
        size_t rows;
        size_t cols;
        std::vector<std::vector<T>> data;

    public:
        Matrix();
        Matrix(const size_t rows, const size_t cols);
        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;
        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;
        ~Matrix() = default;

        size_t getRows() const;
        size_t getCols() const;
        bool isEmpty() const;

        std::vector<T>& operator[](const size_t index);
        const std::vector<T>& operator[](const size_t index) const;

        void resize(const size_t newRows, const size_t newCols);
        void clear();
        void fill(const T& value);

        std::string toString() const;
        std::unique_ptr<Matrix<T>> clone() const;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

    template <typename T>
    std::istream& operator>>(std::istream& is, Matrix<T>& m);

} // namespace miit::algebra
