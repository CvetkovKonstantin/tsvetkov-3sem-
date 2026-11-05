#include "Furniture.h"

Furniture::Furniture(const int id, const std::string& name, const std::string& category,
                     const double price, const int quantity)
    : Product(id, name, category, price, quantity)
{
}

Furniture::Furniture(const std::string& name, const std::string& category,
                     const double price, const int quantity)
    : Product(name, category, price, quantity)
{
}

std::string Furniture::getInfo() const
{
    return "[Готовая] " + Product::getInfo();
}
