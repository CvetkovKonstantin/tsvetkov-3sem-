#include "Client.h"

#include <stdexcept>

Client::Client(const int id, const std::string& name)
    : id(id), name(name)
{
    if (id <= 0 || name.empty())
    {
        throw std::invalid_argument("Неверные данные клиента");
    }
}

Client::~Client() = default;

int Client::getId() const { return id; }
const std::string& Client::getName() const { return name; }

std::string Client::getInfo() const
{
    return name;
}
