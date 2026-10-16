#pragma once

#include "Generator.h"
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace miit::algebra {

    /**
     * @brief Двумерный массив (матрица) размера rows x cols
     * @tparam T Тип элементов матрицы
     *
     * Шаблонный класс. Все методы определены прямо в заголовке —
     * это стандартный подход для шаблонов в C++ (как в STL).
     */
    template <typename T>
    class Matrix {
    private:
        std::vector<std::vector<T>> data;
        std::size_t rows;
        std::size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию (пустая матрица 0x0)
         */
        Matrix()
            : data{}, rows{ 0 }, cols{ 0 }
        {
        }

        /**
         * @brief Конструктор с заданным размером
         * @param rows количество строк
         * @param cols количество столбцов
         */
        Matrix(const std::size_t rows, const std::size_t cols)
            : data(rows, std::vector<T>(cols)), rows{ rows }, cols{ cols }
        {
        }

        /**
         * @brief Конструктор с размером и генератором
         * @param rows количество строк
         * @param cols количество столбцов
         * @param generator генератор значений
         */
        Matrix(const std::size_t rows,
               const std::size_t cols,
               const Generator& generator)
            : Matrix(rows, cols)
        {
            fill(generator);
        }

        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;
        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;
        ~Matrix() = default;

        /**
         * @brief Доступ к строке матрицы по индексу
         * @param index номер строки
         * @throws std::out_of_range если index >= data.size()
         */
        std::vector<T>& operator[](const std::size_t index)
        {
            if (index >= data.size()) {
                throw std::out_of_range("Matrix: row index out of range");
            }
            return data[index];
        }

        /**
         * @brief Доступ к строке матрицы по индексу (константный)
         * @param index номер строки
         * @throws std::out_of_range если index >= data.size()
         */
        const std::vector<T>& operator[](const std::size_t index) const
        {
            if (index >= data.size()) {
                throw std::out_of_range("Matrix: row index out of range");
            }
            return data[index];
        }

        /**
         * @brief Циклический сдвиг каждой строки влево
         * @param shift величина сдвига
         */
        Matrix& operator<<(const std::size_t shift)
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

        /**
         * @brief Циклический сдвиг каждой строки вправо
         * @param shift величина сдвига
         */
        Matrix& operator>>(const std::size_t shift)
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

        /** @brief Количество строк */
        std::size_t getRows() const noexcept
        {
            return data.size();
        }

        /** @brief Количество столбцов */
        std::size_t getCols() const noexcept
        {
            return cols;
        }

        /** @brief Проверить, пустая ли матрица */
        bool isEmpty() const noexcept
        {
            return data.empty() || data[0].empty();
        }

        /**
         * @brief Заполнить матрицу значениями генератора
         * @param generator генератор значений
         */
        void fill(const Generator& generator)
        {
            for (auto& row : data) {
                for (auto& element : row) {
                    element = static_cast<T>(generator.generate());
                }
            }
        }

        /** @brief Преобразовать матрицу в строку */
        std::string toString() const
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

        /**
         * @brief Вставить строку
         * @param index позиция вставки (index == data.size() — в конец)
         * @param row значения строки
         * @throws std::invalid_argument если размер не совпадает
         * @throws std::out_of_range если index > data.size()
         */
        void insertRow(const std::size_t index, const std::vector<T>& row)
        {
            if (row.size() != cols) {
                throw std::invalid_argument("Matrix: row size mismatch");
            }
            if (index > data.size()) {
                throw std::out_of_range("Matrix: row index out of range");
            }
            data.insert(data.begin() + static_cast<std::ptrdiff_t>(index), row);
            rows = data.size();
        }

        /**
         * @brief Удалить строку
         * @param index индекс строки
         * @throws std::out_of_range если index >= data.size()
         */
        void removeRow(const std::size_t index)
        {
            if (index >= data.size()) {
                throw std::out_of_range("Matrix: row index out of range");
            }
            data.erase(data.begin() + static_cast<std::ptrdiff_t>(index));
            rows = data.size();
        }

        /**
         * @brief Вставить столбец
         * @param index позиция вставки (index == cols — в конец)
         * @param col значения столбца
         * @throws std::invalid_argument если размер не совпадает
         * @throws std::out_of_range если index > cols
         */
        void insertCol(const std::size_t index, const std::vector<T>& col)
        {
            if (col.size() != data.size()) {
                throw std::invalid_argument("Matrix: col size mismatch");
            }
            if (index > cols) {
                throw std::out_of_range("Matrix: col index out of range");
            }
            for (std::size_t i = 0; i < data.size(); ++i) {
                data[i].insert(data[i].begin() + static_cast<std::ptrdiff_t>(index),
                               col[i]);
            }
            ++cols;
        }

        /**
         * @brief Удалить столбец
         * @param index индекс столбца
         * @throws std::out_of_range если index >= cols
         */
        void removeCol(const std::size_t index)
        {
            if (index >= cols) {
                throw std::out_of_range("Matrix: col index out of range");
            }
            for (auto& row : data) {
                row.erase(row.begin() + static_cast<std::ptrdiff_t>(index));
            }
            --cols;
        }
    };

} // namespace miit::algebra
