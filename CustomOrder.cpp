#include "CustomOrder.h"

#include <stdexcept>

CustomOrder::CustomOrder(const int id, const Client& client,
                         const Product& product, const int quantity,
                         const std::string& date, const double total,
                         const double markupPercent)
    : Sale(id, client, product, quantity, date, total),
      markupPercent(markupPercent)
{
    if (markupPercent < 0)
    {
        throw std::invalid_argument("Надбавка не может быть отрицательной");
    }
}

CustomOrder::CustomOrder(const Client& client, const Product& product,
                         const int quantity, const std::string& date,
                         const double total, const double markupPercent)
    : Sale(client, product, quantity, date, total),
      markupPercent(markupPercent)
{
    if (markupPercent < 0)
    {
        throw std::invalid_argument("Надбавка не может быть отрицательной");
    }
}

CustomOrder::CustomOrder(const CustomOrder& other)
    : Sale(other), markupPercent(other.markupPercent)
{
}

CustomOrder& CustomOrder::operator=(const CustomOrder& other)
{
    if (this != &other)
    {
        Sale::operator=(other);
        markupPercent = other.markupPercent;
    }
    return *this;
}

CustomOrder::~CustomOrder() = default;

double CustomOrder::getMarkupPercent() const { return markupPercent; }

std::string CustomOrder::getInfo() const
{
    return "Заказ по проекту №" + std::to_string(getId()) +
           " от " + getDate() +
           ", образец №" + std::to_string(getProductId()) +
           ", количество: " + std::to_string(getQuantity()) +
           ", надбавка: " + std::to_string(markupPercent) + "%" +
           ", сумма: " + std::to_string(getTotal());
}
