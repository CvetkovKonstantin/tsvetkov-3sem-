#include "Exercise.h"
#include <utility>

namespace miit::algebra {

    void Exercise::setMatrix(const Matrix<int>& mat) {
        matrix = mat;
    }

    const Matrix<int>& Exercise::getMatrix() const {
        return matrix;
    }

    void Exercise::setGenerator(std::unique_ptr<Generator> gen) {
        generator = std::move(gen);
    }

    Generator* Exercise::getGenerator() const {
        return generator.get();
    }

} 
