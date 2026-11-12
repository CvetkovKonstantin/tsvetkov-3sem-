#include "Sale.h"

#include <algorithm>
#include <stdexcept>

int Sale::nextId = 1;
std::vector<int> Sale::activeIds;

Sale::Sale(const int id, const Client& client, const Product& product,
           const int quantity, const std::string& date, const double total)
    : id(id), client(client), product(product),
      quantity(quantity), date(date), total(total)
{
    if (id <= 0 || client.getId() <= 0 || product.getId() <= 0 ||
        quantity <= 0 || date.empty() || total < 0)
    {
        throw std::invalid_argument("Неверные данные продажи");
    }
    if (std::find(activeIds.begin(), activeIds.end(), id) != activeIds.end())
    {
        throw std::invalid_argument("Продажа с таким ID уже существует");
    }
    activeIds.push_back(id);
    if (id >= nextId)
    {
        nextId = id + 1;
    }
}

Sale::Sale(const Client& client, const Product& product, const int quantity,
           const std::string& date, const double total)
    : Sale(nextId, client, product, quantity, date, total)
{
}

Sale::Sale(const Sale& other)
    : id(other.id), client(other.client), product(other.product),
      quantity(other.quantity), date(other.date), total(other.total)
{
    activeIds.push_back(id);
}

Sale& Sale::operator=(const Sale& other)
{
    if (this != &other)
    {
        client = other.client;
        product = other.product;
        quantity = other.quantity;
        date = other.date;
        total = other.total;
        if (id != other.id)
        {
            activeIds.push_back(other.id);
            const auto it = std::find(activeIds.begin(), activeIds.end(), id);
            if (it != activeIds.end())
            {
                activeIds.erase(it);
            }
            id = other.id;
        }
    }
    return *this;
}

Sale::~Sale()
{
    const auto it = std::find(activeIds.begin(), activeIds.end(), id);
    if (it != activeIds.end())
    {
        activeIds.erase(it);
    }
}

int Sale::getId() const { return id; }
const Client& Sale::getClient() const { return client; }
const Product& Sale::getProduct() const { return product; }
int Sale::getClientId() const { return client.getId(); }
int Sale::getProductId() const { return product.getId(); }
int Sale::getQuantity() const { return quantity; }
const std::string& Sale::getDate() const { return date; }
double Sale::getTotal() const { return total; }

std::string Sale::getInfo() const
{
    return "Продажа №" + std::to_string(id) + " от " + date +
           ", образец №" + std::to_string(getProductId()) +
           ", количество: " + std::to_string(quantity) +
           ", сумма: " + std::to_string(total);
}
