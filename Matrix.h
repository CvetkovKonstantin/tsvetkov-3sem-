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
     * @tparam T тип элементов матрицы
     *
     * Класс не зависит от остальной части решения и может быть
     * использован как самостоятельный контейнер.
     */
    template <typename T>
    class Matrix {
    private:
        std::vector<std::vector<T>> data;
        std::size_t rows;
        std::size_t cols;

    public:
        /**
         * @brief Конструктор по умолчанию (пустая матрица)
         */
        Matrix();

        /**
         * @brief Конструктор с заданным размером
         * @param rows количество строк
         * @param cols количество столбцов
         */
        Matrix(const std::size_t rows, const std::size_t cols);

        /**
         * @brief Конструктор с заданным размером и генератором
         * @param rows количество строк
         * @param cols количество столбцов
         * @param generator генератор значений
         */
        Matrix(const std::size_t rows,
               const std::size_t cols,
               const Generator& generator);

        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;
        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;
        ~Matrix() = default;

        /**
         * @brief Доступ к строке по индексу
         * @param index индекс строки
         * @return ссылка на вектор строки
         * @throws std::out_of_range если индекс вне диапазона
         */
        std::vector<T>& operator[](const std::size_t index);

        /**
         * @brief Доступ к строке по индексу (константный)
         * @param index индекс строки
         * @return константная ссылка на вектор строки
         * @throws std::out_of_range если индекс вне диапазона
         */
        const std::vector<T>& operator[](const std::size_t index) const;

        /**
         * @brief Циклический сдвиг каждой строки влево
         * @param shift величина сдвига
         * @return ссылка на текущий объект
         */
        Matrix& operator<<(const std::size_t shift);

        /**
         * @brief Циклический сдвиг каждой строки вправо
         * @param shift величина сдвига
         * @return ссылка на текущий объект
         */
        Matrix& operator>>(const std::size_t shift);

        /** @brief Количество строк */
        std::size_t getRows() const noexcept;

        /** @brief Количество столбцов */
        std::size_t getCols() const noexcept;

        /** @brief Проверить, пустая ли матрица */
        bool isEmpty() const noexcept;

        /**
         * @brief Заполнить матрицу значениями генератора
         * @param generator генератор значений
         */
        void fill(const Generator& generator);

        /**
         * @brief Преобразовать матрицу в строку
         * @return строковое представление матрицы
         */
        std::string toString() const;

        /**
         * @brief Вставить строку по указанному индексу
         * @param index позиция вставки
         * @param row вектор значений строки
         * @throws std::invalid_argument если размер строки не совпадает
         * @throws std::out_of_range если индекс вне диапазона
         */
        void insertRow(const std::size_t index, const std::vector<T>& row);

        /**
         * @brief Удалить строку по индексу
         * @param index индекс строки
         * @throws std::out_of_range если индекс вне диапазона
         */
        void removeRow(const std::size_t index);

        /**
         * @brief Вставить столбец по указанному индексу
         * @param index позиция вставки
         * @param col вектор значений столбца
         * @throws std::invalid_argument если размер столбца не совпадает
         * @throws std::out_of_range если индекс вне диапазона
         */
        void insertCol(const std::size_t index, const std::vector<T>& col);

        /**
         * @brief Удалить столбец по индексу
         * @param index индекс столбца
         * @throws std::out_of_range если индекс вне диапазона
         */
        void removeCol(const std::size_t index);
    };

} // namespace miit::algebra
