#include "Shop.h"

#include <stdexcept>

namespace
{
    bool isValidDate(const std::string& date)
    {
        if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        {
            return false;
        }

        for (std::size_t i = 0; i < date.size(); ++i)
        {
            if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
            {
                return false;
            }
        }

        const int year = std::stoi(date.substr(0, 4));
        const int month = std::stoi(date.substr(5, 2));
        const int day = std::stoi(date.substr(8, 2));
        if (year == 0 || month < 1 || month > 12 || day < 1)
        {
            return false;
        }

        const int daysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};
        int maxDay = daysInMonth[month - 1];
        const bool leapYear = (year % 4 == 0 && year % 100 != 0) ||
                              year % 400 == 0;
        if (month == 2 && leapYear)
        {
            maxDay = 29;
        }
        return day <= maxDay;
    }
}

Shop::Shop(const std::string& name) : name(name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Название магазина не задано");
    }
}

const std::string& Shop::getName() const { return name; }

void Shop::addProduct(const Product& product)
{
    for (const Product& existing : products)
    {
        if (existing.getId() == product.getId())
        {
            throw std::invalid_argument("Образец с таким ID уже есть");
        }
    }
    products.push_back(product);
}

int Shop::addRetailClient(const RetailClient& client)
{
    for (const RetailClient& existing : retailClients)
    {
        if (existing.getName() == client.getName() &&
            existing.getPhone() == client.getPhone())
        {
            return existing.getId();
        }
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    for (const DesignClient& existing : designClients)
    {
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    retailClients.push_back(client);
    return client.getId();
}

int Shop::addDesignClient(const DesignClient& client)
{
    for (const RetailClient& existing : retailClients)
    {
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    for (const DesignClient& existing : designClients)
    {
        if (existing.getName() == client.getName() &&
            existing.getAddress() == client.getAddress())
        {
            return existing.getId();
        }
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    designClients.push_back(client);
    return client.getId();
}

Product& Shop::findProduct(const int productId)
{
    for (Product& product : products)
    {
        if (product.getId() == productId)
        {
            return product;
        }
    }
    throw std::invalid_argument("Образец мебели не найден");
}

const Product& Shop::getProduct(const int productId) const
{
    for (const Product& product : products)
    {
        if (product.getId() == productId)
        {
            return product;
        }
    }
    throw std::invalid_argument("Образец мебели не найден");
}

const RetailClient& Shop::getRetailClient(const int clientId) const
{
    for (const RetailClient& client : retailClients)
    {
        if (client.getId() == clientId)
        {
            return client;
        }
    }
    throw std::invalid_argument("Розничный покупатель не найден");
}

const DesignClient& Shop::getDesignClient(const int clientId) const
{
    for (const DesignClient& client : designClients)
    {
        if (client.getId() == clientId)
        {
            return client;
        }
    }
    throw std::invalid_argument("Клиент проекта не найден");
}

const std::vector<Sale>& Shop::getAllSales() const { return sales; }

const std::vector<CustomOrder>& Shop::getAllOrders() const { return orders; }

void Shop::receiveProduct(const int productId, const int quantity)
{
    findProduct(productId).addQuantity(quantity);
}

Sale Shop::addSale(const Client& client, const int productId,
                  const int quantity, const std::string& date)
{
    if (!isValidDate(date) || quantity <= 0)
    {
        throw std::invalid_argument("Неверная дата или количество");
    }

    Product& product = findProduct(productId);
    if (quantity > product.getQuantity())
    {
        throw std::runtime_error("Недостаточно изделий в наличии");
    }

    const double total = product.getPrice() * quantity;
    const Sale sale(client, product, quantity, date, total);
    product.removeQuantity(quantity);
    return sale;
}

int Shop::makeSale(const int clientId, const int productId,
                   const int quantity, const std::string& date)
{
    const RetailClient& client = getRetailClient(clientId);
    const Sale sale = addSale(client, productId, quantity, date);
    sales.push_back(sale);
    return sale.getId();
}

double Shop::calculateOrderCost(const int productId, const int quantity,
                                const double markupPercent) const
{
    if (quantity <= 0 || markupPercent < 0)
    {
        throw std::invalid_argument("Неверное количество или надбавка");
    }

    const Product& product = getProduct(productId);
    return product.getPrice() * quantity * (100.0 + markupPercent) / 100.0;
}

double Shop::makeCustomOrder(const int clientId, const int productId,
                             const int quantity, const std::string& date)
{
    const DesignClient& client = getDesignClient(clientId);
    if (!isValidDate(date))
    {
        throw std::invalid_argument("Неверная дата заказа");
    }

    const double total = calculateOrderCost(productId, quantity,
                                            client.getMarkupPercent());
    const CustomOrder order(client, getProduct(productId), quantity, date,
                            total, client.getMarkupPercent());
    orders.push_back(order);
    return total;
}

std::vector<Product> Shop::getAvailableProducts() const
{
    std::vector<Product> result;
    for (const Product& product : products)
    {
        if (product.getQuantity() > 0)
        {
            result.push_back(product);
        }
    }
    return result;
}

int Shop::getSoldQuantity(const int productId, const std::string& startDate,
                          const std::string& endDate) const
{
    getProduct(productId);
    if (!isValidDate(startDate) || !isValidDate(endDate) || startDate > endDate)
    {
        throw std::invalid_argument("Неверный период дат");
    }

    int quantity = 0;
    for (const Sale& sale : sales)
    {
        if (sale.getProductId() == productId &&
            sale.getDate() >= startDate && sale.getDate() <= endDate)
        {
            quantity += sale.getQuantity();
        }
    }
    return quantity;
}

std::vector<Sale> Shop::getSalesBetween(const std::string& startDate,
                                        const std::string& endDate) const
{
    if (!isValidDate(startDate) || !isValidDate(endDate) || startDate > endDate)
    {
        throw std::invalid_argument("Неверный период дат");
    }

    std::vector<Sale> result;
    for (const Sale& sale : sales)
    {
        if (sale.getDate() >= startDate && sale.getDate() <= endDate)
        {
            result.push_back(sale);
        }
    }
    return result;
}

std::vector<CustomOrder> Shop::getOrdersBetween(
    const std::string& startDate, const std::string& endDate) const
{
    if (!isValidDate(startDate) || !isValidDate(endDate) || startDate > endDate)
    {
        throw std::invalid_argument("Неверный период дат");
    }

    std::vector<CustomOrder> result;
    for (const CustomOrder& order : orders)
    {
        if (order.getDate() >= startDate && order.getDate() <= endDate)
        {
            result.push_back(order);
        }
    }
    return result;
}
