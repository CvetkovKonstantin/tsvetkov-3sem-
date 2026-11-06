#include "Sale.h"

#include <stdexcept>

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
}

Sale::~Sale() = default;

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
