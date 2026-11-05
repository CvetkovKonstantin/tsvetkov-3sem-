#include "Client.h"
#include <algorithm>
#include <stdexcept>

int Client::nextId = 1;
std::vector<int> Client::activeIds;

Client::Client(const int id, const std::string& name, const double discount)
    : id(id), name(name), discount(discount)
{
    if (id <= 0 || name.empty() || discount < 0 || discount > 100)
        throw std::invalid_argument("Неверные данные клиента");
    if (std::find(activeIds.begin(), activeIds.end(), id) != activeIds.end())
        throw std::invalid_argument("Клиент с таким ID уже существует");
    activeIds.push_back(id);
    if (id >= nextId) nextId = id + 1;
}

Client::Client(const std::string& name, const double discount)
    : Client(nextId, name, discount) {}

Client::Client(const Client& other)
    : id(other.id), name(other.name), discount(other.discount)
{
    activeIds.push_back(id);
}

Client& Client::operator=(const Client& other)
{
    if (this != &other) {
        name = other.name;
        discount = other.discount;
        if (id != other.id) {
            activeIds.push_back(other.id);
            const auto it = std::find(activeIds.begin(), activeIds.end(), id);
            if (it != activeIds.end()) activeIds.erase(it);
            id = other.id;
        }
    }
    return *this;
}

Client::~Client()
{
    const auto it = std::find(activeIds.begin(), activeIds.end(), id);
    if (it != activeIds.end()) activeIds.erase(it);
}

int Client::getId() const { return id; }
const std::string& Client::getName() const { return name; }
double Client::getDiscount() const { return discount; }

std::string Client::getInfo() const
{
    return name + ", скидка: " + std::to_string(static_cast<int>(discount)) + "%";
}
