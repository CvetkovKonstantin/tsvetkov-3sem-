#include "IStreamGenerator.h"

namespace miit::algebra {

    IStreamGenerator::IStreamGenerator(std::istream& in)
        : in{ in }
    {
    }

    int IStreamGenerator::generate() const
    {
        int value = 0;
        in >> value;
        return value;
    }

} // namespace miit::algebra
