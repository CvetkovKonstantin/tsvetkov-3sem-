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
    Matrix<int
