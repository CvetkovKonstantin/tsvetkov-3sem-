#include "DesignClient.h"

#include <stdexcept>

DesignClient::DesignClient(const int id, const std::string& name,
                           const std::string& address,
                           const double markupPercent)
    : Client(id, name), address(address), markupPercent(markupPercent)
{
    if (address.empty() || markupPercent < 0)
    {
        throw std::invalid_argument("Неверные данные клиента проекта");
    }
}

DesignClient::DesignClient(const std::string& name, const std::string& address,
                           const double markupPercent)
    : Client(name), address(address), markupPercent(markupPercent)
{
    if (address.empty() || markupPercent < 0)
    {
        throw std::invalid_argument("Неверные данные клиента проекта");
    }
}

const std::string& DesignClient::getAddress() const { return address; }
double DesignClient::getMarkupPercent() const { return markupPercent; }

std::string DesignClient::getInfo() const
{
    return "Клиент проекта: " + Client::getInfo() +
           ", адрес: " + address +
           ", надбавка: " + std::to_string(markupPercent) + "%";
}
