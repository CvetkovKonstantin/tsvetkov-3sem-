#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

// ============================================================
// Мини-фреймворк для тестов
// ============================================================

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

    inline int& failed() {
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
            const std::string full = t.suite + "." + t.name;
            try {
                t.fn();
                ++passed;
                std::cout << "[       OK ] " << full << "\n";
            }
            catch (const std::exception& e) {
                ++failed();
                std::cout << "[  FAILED  ] " << full
                          << "  --  " << e.what() << "\n";
            }
            catch (...) {
                ++failed();
                std::cout << "[  FAILED  ] " << full
                          << "  --  unknown exception\n";
            }
        }
        std::cout << "\n[==========] " << registry().size() << " tests ran.\n";
        std::cout << "[  PASSED  ] " << passed << " tests.\n";
        if (failed() > 0) {
            std::cout << "[  FAILED  ] " << failed() << " tests.\n";
        }
        return failed() == 0 ? 0 : 1;
    }

} // namespace mtest

#define TEST(suite, name)                                              \
    static void suite##_##name##_impl();                               \
    static ::mtest::Registrar suite##_##name##_reg(                    \
        #suite, #name, suite##_##name##_impl);                         \
    static void suite##_##name##_impl()

#define EXPECT_TRUE(x)                                                 \
    do { if (!(x)) throw std::runtime_error("EXPECT_TRUE failed"); } while (0)

#define EXPECT_FALSE(x)                                                \
    do { if ((x)) throw std::runtime_error("EXPECT_FALSE failed"); } while (0)

#define EXPECT_EQ(a, b)                                                \
    do {                                                               \
        auto _a = (a); auto _b = (b);                                  \
        if (!(_a == _b)) {                                             \
            std::ostringstream _oss;                                   \
            _oss << "EXPECT_EQ failed: " #a " == " #b                  \
                 << " (" << _a << " vs " << _b << ")";                 \
            throw std::runtime_error(_oss.str());                      \
        }                                                              \
    } while (0)

#define EXPECT_NE(a, b)                                                \
    do { if (!((a) != (b))) throw std::runtime_error("EXPECT_NE failed"); } while (0)

#define EXPECT_GE(a, b)                                                \
    do {                                                               \
        auto _a = (a); auto _b = (b);                                  \
        if (!(_a >= _b))                                               \
            throw std::runtime_error("EXPECT_GE failed");              \
    } while (0)

#define EXPECT_LE(a, b)                                                \
    do {                                                               \
        auto _a = (a); auto _b = (b);                                  \
        if (!(_a <= _b))                                               \
            throw std::runtime_error("EXPECT_LE failed");              \
    } while (0)

#define EXPECT_THROW(stmt, ex)                                         \
    do {                                                               \
        bool _thrown = false;                                          \
        try { stmt; }                                                  \
        catch (const ex&) { _thrown = true; }                          \
        catch (...) {}                                                 \
        if (!_thrown)                                                  \
            throw std::runtime_error("EXPECT_THROW failed");           \
    } while (0)

#define EXPECT_NO_THROW(stmt)                                          \
    do {                                                               \
        try { stmt; }                                                  \
        catch (const std::exception& e) {                              \
            throw std::runtime_error(                                  \
                std::string("EXPECT_NO_THROW failed: ") + e.what());   \
        }                                                              \
        catch (...) {                                                  \
            throw std::runtime_error("EXPECT_NO_THROW failed");        \
        }                                                              \
    } while (0)

// ============================================================
// Тесты Matrix — конструкторы
// ============================================================

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
}

TEST(MatrixConstructor, Copy) {
    Matrix<int> src(2, 2);
    src[0] = { 1, 2 };
    src[1] = { 3, 4 };

    Matrix<int> copy(src);
    EXPECT_EQ(copy[0][0], 1);
    EXPECT_EQ(copy[1][1], 4);

    copy[0][0] = 99;
    EXPECT_EQ(src[0][0], 1);
}

// ============================================================
// Тесты Matrix — операторы присваивания
// ============================================================

TEST(MatrixAssignment, Copy) {
    Matrix<int> src(2, 2);
    src[0] = { 1, 2 };
    src[1] = { 3, 4 };

    Matrix<int> dst;
    dst = src;
    EXPECT_EQ(dst.getRows(), 2u);
    EXPECT_EQ(dst[1][1], 4);
}

TEST(MatrixAssignment, Self) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    m = m;
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
}

// ============================================================
// Тесты Matrix — оператор доступа по индексу
// ============================================================

TEST(MatrixIndex, NonConst) {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixIndex, Const) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    const Matrix<int>& ref = m;
    EXPECT_EQ(ref[0][0], 1);
    EXPECT_EQ(ref[1][1], 4);
}

TEST(MatrixIndex, OutOfRange) {
    Matrix<int> m(2, 2);
    EXPECT_THROW(m[2][0], std::out_of_range);
    EXPECT_THROW(m[5][0], std::out_of_range);
}

// ============================================================
// Тесты Matrix — getRows / getCols / isEmpty
// ============================================================

TEST(MatrixGet, RowsAndCols) {
    Matrix<int> m(5, 7);
    EXPECT_EQ(m.getRows(), 5u);
    EXPECT_EQ(m.getCols(), 7u);
}

TEST(MatrixIsEmpty, True) {
    Matrix<int> m;
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixIsEmpty, False) {
    Matrix<int> m(1, 1);
    EXPECT_FALSE(m.isEmpty());
}

// ============================================================
// Тесты Matrix — resize / clear
// ============================================================

TEST(MatrixResize, Larger) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    m.resize(3, 3);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getCols(), 3u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 4);
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

TEST(MatrixClear, Empty) {
    Matrix<int> m(3, 3);
    m.clear();
    EXPECT_TRUE(m.isEmpty());
}

// ============================================================
// Тесты Matrix — fill и toString
// ============================================================

TEST(MatrixFill, Value) {
    Matrix<int> m(2, 3);
    m.fill(42);
    for (size_t i = 0; i < m.getRows(); ++i)
        for (size_t j = 0; j < m.getCols(); ++j)
            EXPECT_EQ(m[i][j], 42);
}

TEST(MatrixToString, Data) {
    Matrix<int> m(2, 3);
    m[0] = { 1, 2, 3 };
    m[1] = { 4, 5, 6 };
    EXPECT_EQ(m.toString(), "1 2 3 \n4 5 6 \n");
}

TEST(MatrixToString, Empty) {
    Matrix<int> m;
    EXPECT_EQ(m.toString(), "");
}

// ============================================================
// Тесты Matrix — clone
// ============================================================

TEST(MatrixClone, Independent) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    auto copy = m.clone();
    (*copy)[0][0] = 99;
    EXPECT_EQ(m[0][0], 1);
}

// ============================================================
// Тесты генераторов
// ============================================================

TEST(RandomGenerator, InRange) {
    RandomGenerator gen(1, 10);
    for (int i = 0; i < 100; ++i) {
        const int v = gen.generate();
        EXPECT_GE(v, 1);
        EXPECT_LE(v, 10);
    }
}

TEST(RandomGenerator, NegativeRange) {
    RandomGenerator gen(-10, -5);
    for (int i = 0; i < 100; ++i) {
        const int v = gen.generate();
        EXPECT_GE(v, -10);
        EXPECT_LE(v, -5);
    }
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

TEST(ConstantGenerator, Value) {
    ConstantGenerator gen(7);
    EXPECT_EQ(gen.generate(), 7);
    EXPECT_EQ(gen.generate(), 7);
}

TEST(ConstantGenerator, DefaultZero) {
    ConstantGenerator gen;
    EXPECT_EQ(gen.generate(), 0);
}

TEST(ConstantGenerator, SetAndGet) {
    ConstantGenerator gen(1);
    gen.setValue(99);
    EXPECT_EQ(gen.getValue(), 99);
    EXPECT_EQ(gen.generate(), 99);
}

// ============================================================
// Тесты Task1
// ============================================================

TEST(Task1, Basic) {
    Matrix<int> m(3, 3);
    m[0] = { 5, -2, 3 };
    m[1] = { 1,  8, -4 };
    m[2] = { 7, -1, 6 };

    Task1 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    EXPECT_EQ(r[1][0], 0);
    EXPECT_EQ(r[2][1], 0);
    EXPECT_EQ(r[0][2], 0);
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

TEST(Task1, EmptyThrows) {
    Task1 task;
    task.setMatrix(Matrix<int>());
    EXPECT_THROW(task.solve(), std::runtime_error);
}

TEST(Task1, Description) {
    Task1 task;
    EXPECT_EQ(task.getDescription(),
        "Replace the minimum absolute value element of each column with zero");
}

// ============================================================
// Тесты Task2
// ============================================================

TEST(Task2, Basic) {
    Matrix<int> m(2, 4);
    m[0] = { 3, 1, 5, 2 };
    m[1] = { 1, 4, 2, 3 };

    Task2 task;
    task.setMatrix(m);
    task.solve();
    const auto& r = task.getMatrix();

    // Столбец 0: 3 > 1 — удаляем
    // Столбец 1: 1 > 4 — оставляем
    // Столбец 2: 5 > 2 — удаляем
    // Столбец 3: 2 > 3 — оставляем
    EXPECT_EQ(r.getCols(), 2u);
    EXPECT_EQ(r[0][0], 1);
    EXPECT_EQ(r[0][1], 2);
    EXPECT_EQ(r[1][0], 4);
    EXPECT_EQ(r[1][1], 3);
}

TEST(Task2, AllColumnsRemoved) {
    Matrix<int> m(2, 3);
    m[0] = { 5, 7, 2 };
    m[1] = { 1, 3, 0 };

    Task2 task;
    task.setMatrix(m);
    task.solve();
    EXPECT_EQ(task.getMatrix().getCols(), 0u);
}

TEST(Task2, NoColumnsRemoved) {
    Matrix<int> m(2, 3);
    m[0] = { 1, 2, 3 };
    m[1] = { 2, 4, 5 };

    Task2 task;
    task.setMatrix(m);
    task.solve();
    EXPECT_EQ(task.getMatrix().getCols(), 3u);
}

TEST(Task2, EmptyNoThrow) {
    Task2 task;
    task.setMatrix(Matrix<int>());
    EXPECT_NO_THROW(task.solve());
}

TEST(Task2, Description) {
    Task2 task;
    EXPECT_EQ(task.getDescription(),
        "Remove all columns where the first element is greater than the last element");
}

// ============================================================
// Тесты Exercise
// ============================================================

TEST(Exercise, SetAndGetMatrix) {
    Matrix<int> m(2, 2);
    m[0] = { 1, 2 };
    m[1] = { 3, 4 };

    Task1 task;
    task.setMatrix(m);
    EXPECT_EQ(task.getMatrix()[0][0], 1);
    EXPECT_EQ(task.getMatrix()[1][1], 4);
}

TEST(Exercise, SetGenerator) {
    Task1 task;
    auto gen = std::make_unique<RandomGenerator>(1, 10);
    task.setGenerator(std::move(gen));
    EXPECT_NE(task.getGenerator(), nullptr);
}

// ============================================================
// Точка входа
// ============================================================

int main() {
    std::cout << "============================================\n";
    std::cout << "  Unit tests for miit::algebra library\n";
    std::cout << "============================================\n\n";
    return ::mtest::runAll();
}
