#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

constexpr int CONSTANT_VALUE = 7;

enum class FillMethod {
    Random   = 1,
    Manual   = 2,
    Constant = 3
};

size_t readSize(const std::string& message);
FillMethod readChoice();
void fillMatrix(Matrix<int>& matrix, Generator& generator);
void runExercise(Exercise& exercise,
                 const Matrix<int>& original,
                 const std::string& title);

int main() {
    try {
        const size_t rows = readSize("Enter number of rows: ");
        const size_t cols = readSize("Enter number of columns: ");

        Matrix<int> matrix(rows, cols);
        const FillMethod choice = readChoice();

        switch (choice) {
        case FillMethod::Random: {
            int min = 0;
            int max = 0;
            std::cout << "Enter minimum value: ";
            std::cin >> min;
            std::cout << "Enter maximum value: ";
            std::cin >> max;
            if (min > max) {
                std::cerr << "Error: minimum greater than maximum\n";
                return 1;
            }
            RandomGenerator gen(min, max);
            fillMatrix(matrix, gen);
            break;
        }
        case FillMethod::Manual: {
            std::cout << "Enter matrix elements (" << rows * cols << " values):\n";
            IStreamGenerator gen(std::cin);
            fillMatrix(matrix, gen);
            break;
        }
        case FillMethod::Constant: {
            std::cout << "Using constant value: " << CONSTANT_VALUE << "\n";
            ConstantGenerator gen(CONSTANT_VALUE);
            fillMatrix(matrix, gen);
            break;
        }
        default:
            std::cerr << "Error: invalid choice\n";
            return 1;
        }

        std::cout << "\nCreated matrix:\n" << matrix.toString() << "\n";

        Task1 task1;
        runExercise(task1, matrix, "Task 1");

        Task2 task2;
        runExercise(task2, matrix, "Task 2");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}

size_t readSize(const std::string& message) {
    std::cout << message;
    int value = 0;
    std::cin >> value;
    if (value <= 0) {
        std::cerr << "Error: size must be positive\n";
        std::exit(1);
    }
    return static_cast<size_t>(value);
}

FillMethod readChoice() {
    std::cout << "Select matrix filling method:\n"
              << static_cast<int>(FillMethod::Random)   << " - random numbers\n"
              << static_cast<int>(FillMethod::Manual)   << " - manual input\n"
              << static_cast<int>(FillMethod::Constant) << " - constant value\n"
              << "Your choice: ";
    int choice = 0;
    std::cin >> choice;
    return static_cast<FillMethod>(choice);
}

void fillMatrix(Matrix<int>& matrix, Generator& generator) {
    for (size_t i = 0; i < matrix.getRows(); ++i) {
        for (size_t j = 0; j < matrix.getCols(); ++j) {
            matrix[i][j] = generator.generate();
        }
    }
}

void runExercise(Exercise& exercise,
                 const Matrix<int>& original,
                 const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
    std::cout << "Description: " << exercise.getDescription() << "\n\n";
    std::cout << "Original matrix:\n" << original.toString() << "\n";

    exercise.setMatrix(original);
    exercise.solve();

    std::cout << "Result:\n" << exercise.getMatrix().toString() << "\n";
}
