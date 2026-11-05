#include "WholesaleClient.h"
#include <stdexcept>

WholesaleClient::WholesaleClient(const int id, const std::string& name, const double discount, const std::string& contactPerson)
    : Client(id, name, discount), contactPerson(contactPerson)
{
    if (contactPerson.empty()) throw std::invalid_argument("Контактное лицо не указано");
}

WholesaleClient::WholesaleClient(const std::string& name, const double discount, const std::string& contactPerson)
    : Client(name, discount), contactPerson(contactPerson)
{
    if (contactPerson.empty()) throw std::invalid_argument("Контактное лицо не указано");
}

const std::string& WholesaleClient::getContactPerson() const { return contactPerson; }

std::string WholesaleClient::getInfo() const
{
    return "Оптовик: " + Client::getInfo() + ", контакт: " + contactPerson;
}
