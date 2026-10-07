#include "Matrix.h"

namespace miit::algebra {

    template <typename T>
    Matrix<T>::Matrix()
        : data{}, rows{ 0 }, cols{ 0 }
    {
    }

    template <typename T>
    Matrix<T>::Matrix(const std::size_t rows, const std::size_t cols)
        : data(rows, std::vector<T>(cols)), rows{ rows }, cols{ cols }
    {
    }

    template <typename T>
    Matrix<T>::Matrix(const std::size_t rows,
                      const std::size_t cols,
                      const Generator& generator)
        : Matrix(rows, cols)
    {
        fill(generator);
    }

    template <typename T>
    std::vector<T>& Matrix<T>::operator[](const std::size_t index)
    {
        if (index >= rows) {
            throw std::out_of_range("Matrix: row index out of range");
        }
        return data[index];
    }

    template <typename T>
    const std::vector<T>& Matrix<T>::operator[](const std::size_t index) const
    {
        if (index >= rows) {
            throw std::out_of_range("Matrix: row index out of range");
        }
        return data[index];
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator<<(const std::size_t shift)
    {
        if (cols == 0) {
            return *this;
        }
        const std::size_t s = shift % cols;
        for (auto& row : data) {
            std::rotate(row.begin(),
                        row.begin() + static_cast<std::ptrdiff_t>(s),
                        row.end());
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator>>(const std::size_t shift)
    {
        if (cols == 0) {
            return *this;
        }
        const std::size_t s = shift % cols;
        for (auto& row : data) {
            std::rotate(row.begin(),
                        row.end() - static_cast<std::ptrdiff_t>(s),
                        row.end());
        }
        return *this;
    }

    template <typename T>
    std::size_t Matrix<T>::getRows() const noexcept
    {
        return rows;
    }

    template <typename T>
    std::size_t Matrix<T>::getCols() const noexcept
    {
        return cols;
    }

    template <typename T>
    bool Matrix<T>::isEmpty() const noexcept
    {
        return rows == 0 || cols == 0;
    }

    template <typename T>
    void Matrix<T>::fill(const Generator& generator)
    {
        for (auto& row : data) {
            for (auto& element : row) {
                element = static_cast<T>(generator.generate());
            }
        }
    }

    template <typename T>
    std::string Matrix<T>::toString() const
    {
        std::ostringstream out;
        for (const auto& row : data) {
            for (const auto& element : row) {
                out << element << ' ';
            }
            out << '\n';
        }
        return out.str();
    }

    template <typename T>
    void Matrix<T>::insertRow(const std::size_t index, const std::vector<T>& row)
    {
        if (row.size() != cols) {
            throw std::invalid_argument("Matrix: row size mismatch");
        }
        if (index > rows) {
            throw std::out_of_range("Matrix: row index out of range");
        }
        data.insert(data.begin() + static_cast<std::ptrdiff_t>(index), row);
        ++rows;
    }

    template <typename T>
    void Matrix<T>::removeRow(const std::size_t index)
    {
        if (index >= rows) {
            throw std::out_of_range("Matrix: row index out of range");
        }
        data.erase(data.begin() + static_cast<std::ptrdiff_t>(index));
        --rows;
    }

    template <typename T>
    void Matrix<T>::insertCol(const std::size_t index, const std::vector<T>& col)
    {
        if (col.size() != rows) {
            throw std::invalid_argument("Matrix: col size mismatch");
        }
        if (index > cols) {
            throw std::out_of_range("Matrix: col index out of range");
        }
        for (std::size_t i = 0; i < rows; ++i) {
            data[i].insert(data[i].begin() + static_cast<std::ptrdiff_t>(index),
                           col[i]);
        }
        ++cols;
    }

    template <typename T>
    void Matrix<T>::removeCol(const std::size_t index)
    {
        if (index >= cols) {
            throw std::out_of_range("Matrix: col index out of range");
        }
        for (auto& row : data) {
            row.erase(row.begin() + static_cast<std::ptrdiff_t>(index));
        }
        --cols;
    }

    // Явное инстанцирование шаблона для типа int
    template class Matrix<int>;

} // namespace miit::algebra
