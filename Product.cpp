#include "Product.h"
#include <algorithm>
#include <stdexcept>

int Product::nextId = 1;
std::vector<int> Product::activeIds;

Product::Product(const int id, const std::string& name, const std::string& category,
                 const double price, const int quantity)
    : id(id), name(name), category(category), price(price), quantity(quantity)
{
    if (id <= 0 || name.empty() || category.empty() || price < 0 || quantity < 0)
        throw std::invalid_argument("Неверные данные товара");
    if (std::find(activeIds.begin(), activeIds.end(), id) != activeIds.end())
        throw std::invalid_argument("Товар с таким ID уже существует");
    activeIds.push_back(id);
    if (id >= nextId) nextId = id + 1;
}

Product::Product(const std::string& name, const std::string& category,
                 const double price, const int quantity)
    : Product(nextId, name, category, price, quantity) {}

Product::Product(const Product& other)
    : id(other.id), name(other.name), category(other.category),
      price(other.price), quantity(other.quantity)
{
    activeIds.push_back(id);
}

Product& Product::operator=(const Product& other)
{
    if (this != &other) {
        name = other.name;
        category = other.category;
        price = other.price;
        quantity = other.quantity;
        if (id != other.id) {
            activeIds.push_back(other.id);
            const auto it = std::find(activeIds.begin(), activeIds.end(), id);
            if (it != activeIds.end()) activeIds.erase(it);
            id = other.id;
        }
    }
    return *this;
}

Product::~Product()
{
    const auto it = std::find(activeIds.begin(), activeIds.end(), id);
    if (it != activeIds.end()) activeIds.erase(it);
}

int Product::getId() const { return id; }
const std::string& Product::getName() const { return name; }
const std::string& Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

std::string Product::getInfo() const
{
    return name + " [" + category + "], цена: " +
           std::to_string(price) + ", остаток: " +
           std::to_string(quantity) + " шт.";
}

void Product::addQuantity(const int amount)
{
    if (amount <= 0) throw std::invalid_argument("Количество должно быть > 0");
    quantity += amount;
}

void Product::removeQuantity(const int amount)
{
    if (amount <= 0) throw std::invalid_argument("Количество должно быть > 0");
    if (amount > quantity) throw std::runtime_error("Недостаточно товара");
    quantity -= amount;
}
