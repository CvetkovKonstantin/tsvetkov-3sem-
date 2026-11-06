#include "RetailClient.h"

#include <stdexcept>

RetailClient::RetailClient(const int id, const std::string& name,
                           const std::string& phone)
    : Client(id, name), phone(phone)
{
    if (phone.empty())
    {
        throw std::invalid_argument("Телефон покупателя не указан");
    }
}

const std::string& RetailClient::getPhone() const { return phone; }

std::string RetailClient::getInfo() const
{
    return "Розничный покупатель: " + Client::getInfo() +
           ", телефон: " + phone;
}
