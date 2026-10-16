#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <stdexcept>

#include "Matrix.h"
#include "Task1.h"
#include "Task2.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"

using namespace miit::algebra;

// ============================================================
// Тесты класса Matrix — конструкторы
// ============================================================

TEST(MatrixTest, DefaultConstructor)
{
    Matrix<int> m;
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getCols(), 0u);
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixTest, SizeConstructor)
{
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getCols(), 4u);
    EXPECT_FALSE(m.isEmpty());

    for (std::size_t i = 0; i < m.getRows(); ++i)
        for (std::size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], 0);
}

TEST(MatrixTest, ZeroSizeConstructor)
{
    Matrix<int> m(0, 0);
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getCols(), 0u);
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixTest, CopyConstructor)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 3, gen);

    Matrix<int> b = a;
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b.getCols(), 3u);
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][2], 6);

    b[0][0] = 100;
    EXPECT_EQ(a[0][0], 1);
}

TEST(MatrixTest, MoveConstructor)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 3, gen);

    Matrix<int> b = std::move(a);
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b.getCols(), 3u);
    EXPECT_EQ(b[0][0], 1);
}

// ============================================================
// Тесты класса Matrix — операторы присваивания
// ============================================================

TEST(MatrixTest, CopyAssignment)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 2, gen);
    Matrix<int> b;

    b = a;
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b.getCols(), 2u);
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][1], 4);

    b[0][0] = 99;
    EXPECT_EQ(a[0][0], 1);
}

TEST(MatrixTest, MoveAssignment)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 2, gen);
    Matrix<int> b;

    b = std::move(a);
    EXPECT_EQ(b.getRows(), 2u);
    EXPECT_EQ(b[0][0], 1);
    EXPECT_EQ(b[1][1], 4);
}

TEST(MatrixTest, SelfAssignment)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> a(2, 2, gen);

    a = a;
    EXPECT_EQ(a[0][0], 1);
    EXPECT_EQ(a[1][1], 4);
}

// ============================================================
// Тесты класса Matrix — заполнение
// ============================================================

TEST(MatrixTest, FillWithConstant)
{
    ConstantGenerator gen(7);
    Matrix<int> m(2, 3, gen);

    for (std::size_t i = 0; i < m.getRows(); ++i)
        for (std::size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], 7);
}

TEST(MatrixTest, FillWithNegativeConstant)
{
    ConstantGenerator gen(-5);
    Matrix<int> m(3, 3, gen);

    for (std::size_t i = 0; i < m.getRows(); ++i)
        for (std::size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], -5);
}

TEST(MatrixTest, FillFromStream)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][0], 4);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixTest, FillFromStreamWithNegative)
{
    std::istringstream input("-1 -2 3 -4 5 -6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    EXPECT_EQ(m[0][0], -1);
    EXPECT_EQ(m[0][1], -2);
    EXPECT_EQ(m[1][2], -6);
}

// ============================================================
// Тесты класса Matrix — доступ по индексу
// ============================================================

TEST(MatrixTest, IndexOperator)
{
    std::istringstream input("10 20 30 40");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);

    EXPECT_EQ(m[0][0], 10);
    EXPECT_EQ(m[1][1], 40);

    m[0][1] = 99;
    EXPECT_EQ(m[0][1], 99);
}

TEST(MatrixTest, ConstIndexOperator)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    const Matrix<int> m(2, 2, gen);

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTest, IndexOutOfRangeThrows)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW(m[2][0], std::out_of_range);
}

// ============================================================
// Тесты класса Matrix — сдвиги строк
// ============================================================

TEST(MatrixTest, ShiftLeft)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    m << 1;
    EXPECT_EQ(m[0][0], 2);
    EXPECT_EQ(m[0][1], 3);
    EXPECT_EQ(m[0][2], 1);
    EXPECT_EQ(m[1][0], 5);
    EXPECT_EQ(m[1][2], 4);
}

TEST(MatrixTest, ShiftLeftByZero)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    m << 0;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
}

TEST(MatrixTest, ShiftRight)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    m >> 1;
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[0][1], 1);
    EXPECT_EQ(m[0][2], 2);
    EXPECT_EQ(m[1][0], 6);
    EXPECT_EQ(m[1][2], 5);
}

TEST(MatrixTest, ShiftLeftByFullWidth)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    m << 3;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[0][2], 3);
}

// ============================================================
// Тесты класса Matrix — toString
// ============================================================

TEST(MatrixTest, ToStringBasic)
{
    std::istringstream input("1 2 3 4");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);

    EXPECT_EQ(m.toString(), "1 2 \n3 4 \n");
}

TEST(MatrixTest, ToStringEmpty)
{
    Matrix<int> m;
    EXPECT_EQ(m.toString(), "");
}

TEST(MatrixTest, ToStringNegative)
{
    std::istringstream input("-1 -2 -3 -4");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);

    EXPECT_EQ(m.toString(), "-1 -2 \n-3 -4 \n");
}

// ============================================================
// Тесты класса Matrix — insertRow / removeRow
// ============================================================

TEST(MatrixTest, InsertRow)
{
    Matrix<int> m(2, 3);
    std::vector<int> row = { 9, 9, 9 };
    m.insertRow(1, row);

    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[1][0], 9);
    EXPECT_EQ(m[1][2], 9);
}

TEST(MatrixTest, InsertRowAtBeginning)
{
    Matrix<int> m(2, 2);
    std::vector<int> row = { 7, 7 };
    m.insertRow(0, row);

    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[0][0], 7);
}

TEST(MatrixTest, InsertRowWrongSizeThrows)
{
    Matrix<int> m(2, 3);
    std::vector<int> row = { 1, 2 };
    EXPECT_THROW(m.insertRow(0, row), std::invalid_argument);
}

TEST(MatrixTest, RemoveRow)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    m.removeRow(0);
    EXPECT_EQ(m.getRows(), 1u);
    EXPECT_EQ(m[0][0], 4);
    EXPECT_EQ(m[0][2], 6);
}

TEST(MatrixTest, RemoveRowOutOfRangeThrows)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.removeRow(5), std::out_of_range);
}

// ============================================================
// Тесты класса Matrix — insertCol / removeCol
// ============================================================

TEST(MatrixTest, RemoveCol)
{
    std::istringstream input("1 2 3 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    m.removeCol(1);
    EXPECT_EQ(m.getCols(), 2u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 3);
    EXPECT_EQ(m[1][1], 6);
}

TEST(MatrixTest, RemoveColOutOfRangeThrows)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW(m.removeCol(5), std::out_of_range);
}

TEST(MatrixTest, InsertCol)
{
    Matrix<int> m(2, 2);
    std::vector<int> col = { 5, 6 };
    m.insertCol(1, col);

    EXPECT_EQ(m.getCols(), 3u);
    EXPECT_EQ(m[0][1], 5);
    EXPECT_EQ(m[1][1], 6);
}

TEST(MatrixTest, InsertColWrongSizeThrows)
{
    Matrix<int> m(2, 2);
    std::vector<int> col = { 1, 2, 3 };
    EXPECT_THROW(m.insertCol(0, col), std::invalid_argument);
}

// ============================================================
// Тесты Задания 1 (вариант 9): минимальный по модулю в столбце -> 0
// ============================================================

TEST(Task1Test, BasicExample)
{
    // 5 -2  3
    // 1  8 -4
    // 7 -1  6
    std::istringstream input("5 -2 3 1 8 -4 7 -1 6");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[1][0], 0);  // |1| — минимум в столбце 0
    EXPECT_EQ(m[2][1], 0);  // |-1| — минимум в столбце 1
    EXPECT_EQ(m[0][2], 0);  // |3| — минимум в столбце 2

    EXPECT_EQ(m[0][0], 5);
    EXPECT_EQ(m[1][1], 8);
    EXPECT_EQ(m[2][2], 6);
}

TEST(Task1Test, AllPositive)
{
    // 3 7 2
    // 5 1 8
    std::istringstream input("3 7 2 5 1 8");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);  // минимум в столбце 0 = 3
    EXPECT_EQ(m[1][1], 0);  // минимум в столбце 1 = 1
    EXPECT_EQ(m[0][2], 0);  // минимум в столбце 2 = 2
}

TEST(Task1Test, AllNegative)
{
    // -3 -7 -2
    // -5 -1 -8
    std::istringstream input("-3 -7 -2 -5 -1 -8");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 3, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);  // |-3|
    EXPECT_EQ(m[1][1], 0);  // |-1|
    EXPECT_EQ(m[0][2], 0);  // |-2|
}

TEST(Task1Test, SingleRow)
{
    // 3 -7 2 -5
    std::istringstream input("3 -7 2 -5");
    IStreamGenerator gen(input);
    Matrix<int> m(1, 4, gen);

    Task1 task(m);
    task.solve();

    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[0][2], 0);
    EXPECT_EQ(m[0][3], 0);
}

TEST(Task1Test, SingleColumn)
{
    // 3
    // -7
    // 2
    // -5
    std::istringstream input("3 -7 2 -5");
    IStreamGenerator gen(input);
    Matrix<int> m(4, 1, gen);

    Task1 task(m);
    task.solve();

    // Минимальный по модулю — 2 (строка 2)
    EXPECT_EQ(m[2][0], 0);
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[1][0], -7);
    EXPECT_EQ(m[3][0], -5);
}

TEST(Task1Test, EmptyMatrixNoThrow)
{
    Matrix<int> m;
    Task1 task(m);
    EXPECT_NO_THROW(task.solve());
}

// ============================================================
// Тесты Задания 2 (вариант 9)
// ============================================================

TEST(Task2Test, BasicExample)
{
    // 1 2
    // 9 3   <- содержит максимум по модулю (|9|)
    // 4 5   <- последняя
    std::istringstream input("1 2 9 3 4 5");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 4u);
    EXPECT_EQ(m.getCols(), 2u);
    EXPECT_EQ(m[2][0], 4);
    EXPECT_EQ(m[3][0], 4);
    EXPECT_EQ(m[3][1], 5);
}

TEST(Task2Test, OnlyLastRowHasMaxAbs)
{
    std::istringstream input("1 2 9 9");
    IStreamGenerator gen(input);
    Matrix<int> m(2, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m[2][0], 9);
    EXPECT_EQ(m[2][1], 9);
}

TEST(Task2Test, MultipleMaxAbsRows)
{
    //  9  1   <- содержит |9|
    //  2  3
    // -9  4   <- содержит |9|
    //  5  6   <- последняя
    std::istringstream input("9 1 2 3 -9 4 5 6");
    IStreamGenerator gen(input);
    Matrix<int> m(4, 2, gen);

    Task2 task(m);
    task.solve();

    EXPECT_EQ(m.getRows(), 6u);
    EXPECT_EQ(m[1][0], 5);
    EXPECT_EQ(m[4][0], 5);
    EXPECT_EQ(m[5][0], 5);
}

TEST(Task2Test, EmptyMatrixNoThrow)
{
    Matrix<int> m;
    Task2 task(m);
    EXPECT_NO_THROW(task.solve());
}

// ============================================================
// Комбинированный тест
// ============================================================

TEST(CombinedTest, Task1ThenTask2)
{
    std::istringstream input("5 -2 3 1 8 -4 7 -1 6");
    IStreamGenerator gen(input);
    Matrix<int> m(3, 3, gen);

    Task1 t1(m);
    t1.solve();

    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[2][1], 0);
    EXPECT_EQ(m[0][2], 0);

    Task2 t2(m);
    t2.solve();

    // После Task1 максимум по модулю = 8 (строка 1).
    // Значит после строки 1 вставится последняя строка → 4 строки.
    EXPECT_EQ(m.getRows(), 4u);
}
