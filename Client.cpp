#include "Client.h"

#include <algorithm>
#include <stdexcept>

int Client::nextId = 1;
std::vector<int> Client::activeIds;

Client::Client(const int id, const std::string& name)
    : id(id), name(name)
{
    if (id <= 0 || name.empty())
    {
        throw std::invalid_argument("Неверные данные клиента");
    }
    if (std::find(activeIds.begin(), activeIds.end(), id) != activeIds.end())
    {
        throw std::invalid_argument("Клиент с таким ID уже существует");
    }
    activeIds.push_back(id);
    if (id >= nextId)
    {
        nextId = id + 1;
    }
}

Client::Client(const std::string& name)
    : Client(nextId, name)
{
}

int Client::getId() const { return id; }
const std::string& Client::getName() const { return name; }

std::string Client::getInfo() const
{
    return name;
}
