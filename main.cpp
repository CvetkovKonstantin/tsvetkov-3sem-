#include <cstdlib>
#include <iostream>
#include <string>

#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

constexpr int PRESET_CONSTANT_VALUE = 7;

enum class FillMethod {
    Random   = 1,
    Manual   = 2,
    Constant = 3
};

size_t getSize(const std::string& message);
FillMethod getChoice();
void fillMatrix(Matrix<int>& matrix, Generator& generator);
void demonstrateExercise(Exercise& exercise,
                         const Matrix<int>& original,
                         const std::string& taskName);

int main() {
    try {
        const size_t rows = getSize("Enter number of rows: ");
        const size_t cols = getSize("Enter number of columns: ");

        Matrix<int> matrix(rows, cols);
        const FillMethod choice = getChoice();

        switch (choice) {
        case FillMethod::Random: {
            std::cout << "Enter minimum value: ";
            int min = 0;
            std::cin >> min;
            std::cout << "Enter maximum value: ";
            int max = 0;
            std::cin >> max;
            if (min > max) {
                std::cerr << "Error: minimum value is greater than maximum\n";
                return 1;
            }
            RandomGenerator generator(min, max);
            fillMatrix(matrix, generator);
            break;
        }
        case FillMethod::Manual: {
            std::cout << "Enter matrix elements (separated by spaces):\n";
            IStreamGenerator generator(std::cin);
            fillMatrix(matrix, generator);
            break;
        }
        case FillMethod::Constant: {
            std::cout << "Using constant value: " << PRESET_CONSTANT_VALUE << "\n";
            ConstantGenerator generator(PRESET_CONSTANT_VALUE);
            fillMatrix(matrix, generator);
            break;
        }
        default:
            std::cerr << "Error: invalid choice\n";
            return 1;
        }

        std::cout << "\nCreated matrix:\n";
        std::cout << matrix.toString() << "\n";

        Task1 task1;
        demonstrateExercise(task1, matrix, "Task 1");

        Task2 task2;
        demonstrateExercise(task2, matrix, "Task 2");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    std::cin.get();
    return 0;
}

size_t getSize(const std::string& message) {
    std::cout << message;
    int value = 0;
    std::cin >> value;
    if (value <= 0) {
        std::cerr << "Error: size must be positive\n";
        std::exit(1);
    }
    return static_cast<size_t>(value);
}

FillMethod getChoice() {
    std::cout << "Select array filling method:\n"
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

void demonstrateExercise(Exercise& exercise,
                         const Matrix<int>& original,
                         const std::string& taskName) {
    std::cout << "\n=== " << taskName << " ===\n";
    std::cout << "Description: " << exercise.getDescription() << "\n\n";

    std::cout << "Original matrix:\n";
    std::cout << original.toString() << "\n";

    exercise.setMatrix(original);
    exercise.solve();

    std::cout << "Result:\n";
    std::cout << exercise.getMatrix().toString() << "\n";
}
