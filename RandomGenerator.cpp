#include "RandomGenerator.h"

namespace miit::algebra {

    RandomGenerator::RandomGenerator(const int min, const int max)
        : generator{ std::mt19937(std::random_device{}()) },
          distribution{ std::uniform_int_distribution<int>(min, max) }
    {
    }

    int RandomGenerator::generate() const
    {
        return distribution(generator);
    }

} // namespace miit::algebra
