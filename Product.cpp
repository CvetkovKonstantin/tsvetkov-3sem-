#include "Product.h"

#include <stdexcept>

Product::Product(const int id, const std::string& name,
                 const std::string& manufacturer, const double price,
                 const int quantity)
    : id(id), name(name), manufacturer(manufacturer),
      price(price), quantity(quantity)
{
    if (id <= 0 || name.empty() || manufacturer.empty() ||
        price <= 0 || quantity < 0)
    {
        throw std::invalid_argument("Неверные данные образца мебели");
    }
}

int Product::getId() const { return id; }
const std::string& Product::getName() const { return name; }
const std::string& Product::getManufacturer() const { return manufacturer; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

std::string Product::getInfo() const
{
    return "Образец №" + std::to_string(id) + ": " + name +
           ", фабрика: " + manufacturer +
           ", цена: " + std::to_string(price) +
           ", в наличии: " + std::to_string(quantity) + " шт.";
}

void Product::addQuantity(const int amount)
{
    if (amount <= 0)
    {
        throw std::invalid_argument("Количество поступления должно быть положительным");
    }
    quantity += amount;
}

void Product::removeQuantity(const int amount)
{
    if (amount <= 0)
    {
        throw std::invalid_argument("Количество списания должно быть положительным");
    }
    if (amount > quantity)
    {
        throw std::runtime_error("Недостаточно изделий на складе магазина");
    }
    quantity -= amount;
}
