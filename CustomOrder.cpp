#include "CustomOrder.h"
#include <stdexcept>

namespace {
    /**
     * @brief Вычислить цену с наценкой, проверив аргументы
     */
    double calcCustomPrice(const double basePrice, const double markupPercent)
    {
        if (markupPercent < 0) throw std::invalid_argument("Наценка < 0");
        if (basePrice < 0) throw std::invalid_argument("Базовая цена < 0");
        return basePrice * (1.0 + markupPercent / 100.0);
    }
}

CustomOrder::CustomOrder(const int id, const std::string& name, const std::string& category,
                         const double basePrice, const double markupPercent)
    : Product(id, name, category, calcCustomPrice(basePrice, markupPercent), 0),
      basePrice(basePrice), markupPercent(markupPercent)
{
}

CustomOrder::CustomOrder(const std::string& name, const std::string& category,
                         const double basePrice, const double markupPercent)
    : Product(name, category, calcCustomPrice(basePrice, markupPercent), 0),
      basePrice(basePrice), markupPercent(markupPercent)
{
}

double CustomOrder::getBasePrice() const { return basePrice; }
double CustomOrder::getMarkupPercent() const { return markupPercent; }

std::string CustomOrder::getInfo() const
{
    return "[Индивидуальный, наценка " + std::to_string(static_cast<int>(markupPercent)) + "%] " + Product::getInfo();
}
