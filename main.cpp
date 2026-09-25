#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Matrix.h"
#include "Task1.h"
#include "Task2.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"

using namespace miit::algebra;

namespace mtest {

    struct TestCase {
        std::string suite;
        std::string name;
        std::function<void()> fn;
    };

    inline std::vector<TestCase>& registry() {
        static std::vector<TestCase> r;
        return r;
    }

    inline int& failedCount() {
        static int f = 0;
        return f;
    }

    struct Registrar {
        Registrar(const std::string& suite,
                  const std::string& name,
                  std::function<void()> fn) {
            registry().push_back({ suite, name, std::move(fn) });
        }
    };

    inline int runAll() {
        std::cout << "[==========] Running " << registry().size()
                  << " tests.\n\n";
        int passed = 0;
        for (auto& t : registry()) {
            const std::string fullName = t.suite + "." + t.name;
            try {
                t.fn();
                ++passed;
                std::cout << "[       OK ] " << fullName << "\n";
            }
            catch (const std::exception& e) {
                ++failedCount();
                std::cout << "[  FAILED  ] " << fullName
                          << "  --  " << e.what() << "\n";
            }
            catch (...) {
                ++failedCount();
                std::cout << "[  FAILED  ] " << fullName
                          << "  --  unknown exception\n";
            }
        }
        std::cout << "\n[==========] " << registry().size()
                  << " tests ran.\n";
        std::cout << "[  PASSED  ] " << passed << " tests.\n";
        if (failedCount() > 0) {
            std::cout << "[  FAILED  ] " << failedCount() << " tests.\n";
        }
        return failedCount() == 0 ? 0 : 1;
    }

} // namespace mtest

#define TEST(suite, name)                                              \
    static void suite##_##name##_impl();                               \
    static ::mtest::Registrar suite##_##name##_reg(                    \
        #suite, #name, suite##_##name##_impl);                         \
    static void suite##_##name##_impl()

#define EXPECT_TRUE(x)                                                 \
    do {                                                               \
        if (!(x))                                                      \
            throw std::runtime_error("EXPECT_TRUE failed: " #x);       \
    } while (0)

#define EXPECT_FALSE(x)                                                \
    do {                                                               \
        if ((x))                                                       \
            throw std::runtime_error("EXPECT_FALSE failed: " #x);      \
    } while (0)

#define EXPECT_EQ(a, b)                                                \
    do {                                                               \
        auto _a = (a); auto _b = (b);                                  \
        if (!(_a == _b)) {                                             \
            std::ostringstream _oss;                                   \
            _oss << "EXPECT_EQ failed: " #a " == " #b                  \
                 << " (left=" << _a << ", right=" << _b << ")";        \
            throw std::runtime_error(_oss.str());                      \
        }                                                              \
    } while (0)

#define EXPECT_NE(a, b)                                                \
    do {                                                               \
        if (!((a) != (b)))                                             \
            throw std::runtime_error("EXPECT_NE failed: " #a " != " #b); \
    } while (0)

#define EXPECT_GE(a, b)                                                \
    do {                                                               \
        auto _a = (a); auto _b = (b);                                  \
        if (!(_a >= _b)) {                                             \
            std::ostringstream _oss;                                   \
            _oss << "EXPECT_GE failed: " #a " >= " #b                  \
                 << " (left=" << _a << ", right=" << _b << ")";        \
            throw std::runtime_error(_oss.str());                      \
        }                                                              \
    } while (0)

#define EXPECT_LE(a, b)                                                \
    do {                                                               \
        auto _a = (a); auto _b = (b);                                  \
        if (!(_a <= _b)) {                                             \
            std::ostringstream _oss;                                   \
            _oss << "EXPECT_LE failed: " #a " <= " #b                  \
                 << " (left=" << _a << ", right=" << _b << ")";        \
            throw std::runtime_error(_oss.str());                      \
        }                                                              \
    } while (0)

#define EXPECT_THROW(stmt, ex)                                         \
    do {                                                               \
        bool _thrown = false;                                          \
        try { stmt; }                                                  \
        catch (const ex&) { _thrown = true; }                          \
        catch (...) {}                                                 \
        if (!_thrown)                                                  \
            throw std::runtime_error("EXPECT_THROW failed: " #stmt     \
                                     " did not throw " #ex);           \
    } while (0)

#define EXPECT_NO_THROW(stmt)                                          \
    do {                                                               \
        try { stmt; }                                                  \
        catch (const std::exception& e) {                              \
            throw std::runtime_error(                                  \
                std::string("EXPECT_NO_THROW failed: ") + e.what());   \
        }                                                              \
        catch (...) {                                                  \
            throw std::runtime_error("EXPECT_NO_THROW failed: " #stmt);\
        }                                                              \
    } while (0)

TEST(MatrixConstructor, Default) {
    Matrix<int> m;
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getCols(), 0u);
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixConstructor, Parameterized) {
    Matrix<int> m(3, 4);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getCols(), 4u);
    EXPECT_FALSE(m.isEmpty());
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 4; ++j)
            EXPECT_EQ(m[i][j], 0);
}

TEST(MatrixConstructor, Copy) {
    Matrix<int> src(2, 2);
    src[0] = { 1, 2 };
    src[1] = { 3, 4 };

    Matrix<int> copy(src);
    EXPECT_EQ(copy.getRows(), 2u);
    EXPECT_EQ(copy.getCols(), 2u);
    EXPECT_EQ(copy[0][0], 1);
    EXPECT_EQ(copy[1][1], 4);

    // Копия независима от источника
    copy[0][0] = 99;
    EXPECT_EQ(src[0][0], 1);
}

TEST(MatrixConstructor, Move) {
    Matrix<int> src(2, 2);
    src[0] = { 1, 2 };
    src[1] = { 3, 4 };

    Matrix<int> dst(std::move(src));
    EXPECT_EQ(dst.getRows(), 2u);
    EXPECT_EQ(dst.getCols(), 2u);
    EXPECT_EQ(dst[1][1], 4);
}

TEST(MatrixAssignment, Copy) {
    Matrix<int> src(2, 2);
    src[0] = { 1, 2 };
    src[1] = { 3, 4 };

    Matrix<int> dst;
    dst = src;
    EXPECT_EQ(dst.getRows(), 2u);
    EXPECT_EQ(dst[0][0], 1);
    EXPECT_EQ(dst[1][1], 4);
}

TEST(MatrixAssignment, Move) {
    Matrix<int> src(2, 2);
    src[0] = { 5, 6 };
    src[1] = { 7, 8 };

    Matrix<int> dst;
    dst = std::move(src);
    EXPECT_EQ(dst[0][0], 5);
    EXPECT_EQ(dst[1][1], 8);
}

TEST(MatrixAssignment, Self) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    m = m;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixIndex, NonConstAccess) {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixIndex, ConstAccess) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    const Matrix<int>& ref = m;
    EXPECT_EQ(ref[0][0], 1);
    EXPECT_EQ(ref[1][1], 4);
}

TEST(MatrixIndex, OutOfRangeThrows) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m[2][0], std::out_of_range);
    EXPECT_THROW(m[5][0], std::out_of_range);
}

TEST(MatrixGet, RowsAndCols) {
    Matrix<int> m(5, 7);
    EXPECT_EQ(m.getRows(), 5u);
    EXPECT_EQ(m.getCols(), 7u);
}

TEST(MatrixIsEmpty, Empty) {
    Matrix<int> m;
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixIsEmpty, NonEmpty) {
    Matrix<int> m(1, 1);
    EXPECT_FALSE(m.isEmpty());
}

TEST(MatrixResize, Larger) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    m.resize(3, 3);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getCols(), 3u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
    EXPECT_EQ(m[2][2], 0);
}

TEST(MatrixResize, Smaller) {
    Matrix<int> m(3, 3);
    m[0] = { 1, 2, 3 };
    m[1] = { 4, 5, 6 };
    m[2] = { 7, 8, 9 };

    m.resize(2, 2);
    EXPECT_EQ(m.getRows(), 2u);
    EXPECT_EQ(m.getCols(), 2u);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 4);
}

TEST(MatrixClear, MakesEmpty) {
    Matrix<int> m(3, 3);
    m.clear();
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getCols(), 0u);
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixFill, WithValue) {
    Matrix<int> m(2, 3);
    m.fill(42);
    for (size_t i = 0; i < m.getRows(); ++i)
        for (size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], 42);
}

TEST(MatrixFill, OverwritesExisting) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };
    m.fill(0);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[1][1], 0);
}

TEST(MatrixToString, WithData) {
    Matrix<int> m(2, 3);
    m[0] = { 1, 2, 3 };
    m[1] = { 4, 5, 6 };
    EXPECT_EQ(m.toString(), "1 2 3 \n4 5 6 \n");
}

TEST(MatrixToString, Empty) {
    Matrix<int> m;
    EXPECT_EQ(m.toString(), "");
}

TEST(MatrixToString, Negative) {
    Matrix<int> m(1, 2);
    m[0] = { -1, -2 };
    EXPECT_EQ(m.toString(), "-1 -2 \n");
}

TEST(MatrixClone, IndependentCopy) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    auto copy = m.clone();
    EXPECT_EQ(copy->getRows(), 2u);
    EXPECT_EQ((*copy)[0][0], 1);
    (*copy)[0][0] = 99;
    EXPECT_EQ(m[0][0], 1);
}

TEST(RandomGenerator, InRange) {
    RandomGenerator gen(1, 10);
    for (int i = 0; i < 200; ++i) {
        const int v = gen.generate();
        EXPECT_GE(v, 1);
        EXPECT_LE(v, 10);
    }
}

TEST(RandomGenerator, SingleValue) {
    RandomGenerator gen(5, 5);
    for (int i = 0; i < 20; ++i)
        EXPECT_EQ(gen.generate(), 5);
}

TEST(RandomGenerator, NegativeRange) {
    RandomGenerator gen(-10, -5);
    for (int i = 0; i < 100; ++i) {
        const int v = gen.generate();
        EXPECT_GE(v, -10);
        EXPECT_LE(v, -5);
    }
}

TEST(IStreamGenerator, SingleValue) {
    std::stringstream ss("42");
    IStreamGenerator gen(ss);
    EXPECT_EQ(gen.generate(), 42);
}

TEST(IStreamGenerator, MultipleValues) {
    std::stringstream ss("10 20 30");
    IStreamGenerator gen(ss);
    EXPECT_EQ(gen.generate(), 10);
    EXPECT_EQ(gen.generate(), 20);
    EXPECT_EQ(gen.generate(), 30);
}

TEST(IStreamGenerator, Negative) {
    std::stringstream ss("-42");
    IStreamGenerator gen(ss);
    EXPECT_EQ(gen.generate(), -42);
}

TEST(ConstantGenerator, ReturnsConstructorValue) {
    ConstantGenerator gen(7);
    EXPECT_EQ(gen.generate(), 7);
    EXPECT_EQ(gen.generate(), 7);
    EXPECT_EQ(gen.generate(), 7);
}

TEST(ConstantGenerator, DefaultIsZero) {
    ConstantGenerator gen;
    EXPECT_EQ(gen.generate(), 0);
}

TEST(ConstantGenerator, SetAndGetValue) {
    ConstantGenerator gen(1);
    gen.setValue(99);
    EXPECT_EQ(gen.getValue(), 99);
    EXPECT_EQ(gen.generate(), 99);
}


// Task1 — минимальный по модулю элемент каждого столбца → 0

TEST(Task1, BasicCase) {
    Matrix<int> m(3, 3);
    m[0] = { 5, -2, 3 };
    m[1] = { 1,  8, -4 };
    m[2] = { 7, -1, 6 };

    Task1 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    EXPECT_EQ(r[1][0], 0);  // |1| — минимальный в столбце 0
    EXPECT_EQ(r[2][1], 0);  // |-1| — минимальный в столбце 1
    EXPECT_EQ(r[0][2], 0);  // |3| — минимальный в столбце 2
}

TEST(Task1, AllPositive) {
    Matrix<int> m(2, 3);
    m[0] = { 3, 7, 2 };
    m[1] = { 5, 1, 8 };

    Task1 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    EXPECT_EQ(r[0][0], 0);
    EXPECT_EQ(r[1][1], 0);
    EXPECT_EQ(r[0][2], 0);
}

TEST(Task1, AllNegative) {
    Matrix<int> m(2, 3);
    m[0] = { -3, -7, -2 };
    m[1] = { -5, -1, -8 };

    Task1 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    EXPECT_EQ(r[0][0], 0);
    EXPECT_EQ(r[1][1], 0);
    EXPECT_EQ(r[0][2], 0);
}

TEST(Task1, SingleRow) {
    Matrix<int> m(1, 4);
    m[0] = { 3, -7, 2, -5 };

    Task1 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    EXPECT_EQ(r[0][0], 0);
    EXPECT_EQ(r[0][1], 0);
    EXPECT_EQ(r[0][2], 0);
    EXPECT_EQ(r[0][3], 0);
}

TEST(Task1, SingleColumn) {
    Matrix<int> m(4, 1);
    m[0] = { 3 };
    m[1] = { -7 };
    m[2] = { 2 };
    m[3] = { -5 };

    Task1 task;
    task.setMatrix(m);
    task.solve();
    EXPECT_EQ(task.getMatrix()[2][0], 0);  // |2| — минимальный
}

TEST(Task1, EmptyMatrixThrows) {
    Task1 task;
    task.setMatrix(Matrix<int>());
    EXPECT_THROW(task.solve(), std::runtime_error);
}

TEST(Task1, Description) {
    Task1 task;
    EXPECT_EQ(task.getDescription(),
        "Replace the minimum absolute value element of each column with zero");
}

// Task2 — вставить последнюю строку после каждой строки,
//         содержащей максимальный по модулю элемент

TEST(Task2, InsertAfterRowWithMaxAbs) {
    Matrix<int> m(3, 2);
    m[0] = { 1, 2 };
    m[1] = { 9, 3 };  // содержит максимум по модулю (|9|)
    m[2] = { 4, 5 };  // последняя строка

    Task2 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    // Ожидаем: [1,2], [9,3], [4,5], [4,5]
    EXPECT_EQ(r.getRows(), 4u);
    EXPECT_EQ(r.getCols(), 2u);
    EXPECT_EQ(r[2][0], 4);
    EXPECT_EQ(r[3][0], 4);
    EXPECT_EQ(r[3][1], 5);
}

TEST(Task2, OnlyLastRowHasMaxAbs) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 9, 9 };

    Task2 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    EXPECT_EQ(r.getRows(), 3u);
    EXPECT_EQ(r[2][0], 9);
    EXPECT_EQ(r[2][1], 9);
}

TEST(Task2, MultipleMaxAbsRows) {
    Matrix<int> m(4, 2);
    m[0] = { 9, 1 };   // содержит максимум
    m[1] = { 2, 3 };
    m[2] = { -9, 4 };  // содержит максимум (|−9| = 9)
    m[3] = { 5, 6 };

    Task2 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    // 4 исходных + 2 вставки = 6 строк
    EXPECT_EQ(r.getRows(), 6u);
    EXPECT_EQ(r[1][0], 5);   // вставка после строки 0
    EXPECT_EQ(r[4][0], 5);   // вставка после строки 2
}

TEST(Task2, EmptyMatrixNoThrow) {
    Task2 task;
    task.setMatrix(Matrix<int>());
    EXPECT_NO_THROW(task.solve());
}

TEST(Task2, Description) {
    Task2 task;
    EXPECT_EQ(task.getDescription(),
        "Insert the last row after each row containing the maximum absolute value element");
}

TEST(Exercise, SetAndGetMatrix) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    Task1 task;
    task.setMatrix(m);
    const auto& r = task.getMatrix();
    EXPECT_EQ(r[0][0], 1);
    EXPECT_EQ(r[1][1], 4);
}

TEST(Exercise, SetGenerator) {
    Task1 task;
    auto gen = std::make_unique<RandomGenerator>(1, 10);
    task.setGenerator(std::move(gen));
    EXPECT_NE(task.getGenerator(), nullptr);
}

TEST(Integration, Task1ThenTask2) {
    Matrix<int> m(3, 3);
    m[0] = { 5, -2, 3 };
    m[1] = { 1,  8, -4 };
    m[2] = { 7, -1, 6 };

    Task1 task1;
    task1.setMatrix(m);
    task1.solve();

    Task2 task2;
    task2.setMatrix(task1.getMatrix());
    task2.solve();

    EXPECT_FALSE(task2.getMatrix().isEmpty());
}

TEST(Integration, GeneratorFillsMatrix) {
    Matrix<int> m(3, 3);
    ConstantGenerator gen(7);
    for (size_t i = 0; i < m.getRows(); ++i)
        for (size_t j = 0; j < m.getCols(); ++j)
            m[i][j] = gen.generate();

    EXPECT_EQ(m[0][0], 7);
    EXPECT_EQ(m[2][2], 7);
}

// ============================================================
// Точка входа
// ============================================================

int main() {
    std::cout << "============================================\n";
    std::cout << "  Unit tests for miit::algebra library\n";
    std::cout << "  Task 4.3, variant 9\n";
    std::cout << "============================================\n\n";

    return ::mtest::runAll();
}
