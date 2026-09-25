#pragma once

#include <memory>
#include <string>
#include <vector>

namespace miit::algebra {

    /**
     * @brief Шаблонный класс матрицы (двумерного массива)
     * @tparam T тип элементов
     *
     * Не зависит от остальных классов решения и может быть
     * скопирован в любой другой проект без изменений.
     */
    template <typename T>
    class Matrix {
    private:
        /** @brief Количество строк */
        size_t rows;

        /** @brief Количество столбцов */
        size_t cols;

        /** @brief Данные — вектор строк */
        std::vector<std::vector<T>> data;

    public:
        /** @brief Конструктор по умолчанию (пустая матрица 0x0) */
        Matrix();

        /**
         * @brief Конструктор с заданным размером
         * @param rows количество строк
         * @param cols количество столбцов
         */
        Matrix(const size_t rows, const size_t cols);

        Matrix(const Matrix& other) = default;
        Matrix(Matrix&& other) noexcept = default;
        Matrix& operator=(const Matrix& other) = default;
        Matrix& operator=(Matrix&& other) noexcept = default;
        ~Matrix() = default;

        /** @brief Получить количество строк */
        size_t getRows() const;

        /** @brief Получить количество столбцов */
        size_t getCols() const;

        /** @brief Проверить, пустая ли матрица */
        bool isEmpty() const;

        /**
         * @brief Доступ к строке матрицы по индексу
         * @param index индекс строки
         * @throws std::out_of_range если индекс вне диапазона
         */
        std::vector<T>& operator[](const size_t index);

        /**
         * @brief Доступ к строке матрицы по индексу (константный)
         * @param index индекс строки
         * @throws std::out_of_range если индекс вне диапазона
         */
        const std::vector<T>& operator[](const size_t index) const;

        /**
         * @brief Изменить размер матрицы
         * @param newRows новое количество строк
         * @param newCols новое количество столбцов
         */
        void resize(const size_t newRows, const size_t newCols);

        /** @brief Очистить матрицу (сделать пустой) */
        void clear();

        /**
         * @brief Заполнить матрицу одним значением
         * @param value значение для заполнения
         */
        void fill(const T& value);

        /** @brief Преобразовать матрицу в строку */
        std::string toString() const;

        /** @brief Создать копию матрицы */
        std::unique_ptr<Matrix<T>> clone() const;
    };

} 
