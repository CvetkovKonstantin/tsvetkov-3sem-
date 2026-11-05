#include "Store.h"
#include <stdexcept>

Store::Store(const int id, const std::string& name, const double discount, const std::string& address)
    : Client(id, name, discount), address(address)
{
    if (address.empty()) throw std::invalid_argument("Адрес не задан");
}

Store::Store(const std::string& name, const double discount, const std::string& address)
    : Client(name, discount), address(address)
{
    if (address.empty()) throw std::invalid_argument("Адрес не задан");
}

const std::string& Store::getAddress() const { return address; }

std::string Store::getInfo() const
{
    return "Магазин: " + Client::getInfo() + ", адрес: " + address;
}
