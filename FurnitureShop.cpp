#include "FurnitureShop.h"
#include "CustomOrder.h"

#include <stdexcept>
#include <utility>

namespace
{
    /**
     * @brief Проверить корректность даты в формате ГГГГ-ММ-ДД
     * @param date Строка даты
     * @return true если дата корректна, иначе false
     */
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

FurnitureShop::FurnitureShop(const std::string& name)
    : name(name), nextSaleId(1)
{
    if (name.empty())
    {
        throw std::invalid_argument("Название не задано");
    }
}

const std::string& FurnitureShop::getName() const { return name; }

void FurnitureShop::addProduct(std::unique_ptr<Product> product)
{
    if (!product)
    {
        throw std::invalid_argument("Пустой указатель");
    }
    for (const auto& existing : products)
    {
        if (existing->getId() == product->getId())
        {
            throw std::invalid_argument("Товар с таким ID уже есть");
        }
    }
    products.push_back(std::move(product));
}

int FurnitureShop::addStore(const Store& store)
{
    for (const Store& existing : stores)
    {
        if (existing.getName() == store.getName() &&
            existing.getAddress() == store.getAddress())
        {
            return existing.getId();
        }
        if (existing.getId() == store.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    for (const WholesaleClient& existing : wholesaleClients)
    {
        if (existing.getId() == store.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    stores.push_back(store);
    return store.getId();
}

int FurnitureShop::addWholesaleClient(const WholesaleClient& client)
{
    for (const Store& existing : stores)
    {
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    for (const WholesaleClient& existing : wholesaleClients)
    {
        if (existing.getName() == client.getName() &&
            existing.getContactPerson() == client.getContactPerson())
        {
            return existing.getId();
        }
        if (existing.getId() == client.getId())
        {
            throw std::invalid_argument("Клиент с таким ID уже есть");
        }
    }
    wholesaleClients.push_back(client);
    return client.getId();
}

Product& FurnitureShop::findProduct(const int productId)
{
    for (auto& product : products)
    {
        if (product->getId() == productId)
        {
            return *product;
        }
    }
    throw std::invalid_argument("Товар не найден");
}

const Product& FurnitureShop::getProduct(const int productId) const
{
    for (const auto& product : products)
    {
        if (product->getId() == productId)
        {
            return *product;
        }
    }
    throw std::invalid_argument("Товар не найден");
}

const Store& FurnitureShop::getStore(const int storeId) const
{
    for (const Store& store : stores)
    {
        if (store.getId() == storeId)
        {
            return store;
        }
    }
    throw std::invalid_argument("Магазин не найден");
}

const WholesaleClient& FurnitureShop::getWholesaleClient(const int clientId) const
{
    for (const WholesaleClient& client : wholesaleClients)
    {
        if (client.getId() == clientId)
        {
            return client;
        }
    }
    throw std::invalid_argument("Оптовик не найден");
}

const std::vector<Sale>& FurnitureShop::getAllSales() const { return sales; }

void FurnitureShop::receiveProduct(const int productId, const int quantity)
{
    findProduct(productId).addQuantity(quantity);
}

int FurnitureShop::addSale(const Client& client, const int productId,
                           const int quantity, const double discount,
                           const std::string& date)
{
    if (!isValidDate(date) || quantity <= 0)
    {
        throw std::invalid_argument("Неверная дата или количество");
    }

    Product& product = findProduct(productId);

    if (!product.isMadeToOrder())
    {
        if (quantity > product.getQuantity())
        {
            throw std::runtime_error("Недостаточно товара");
        }
        product.removeQuantity(quantity);
    }

    const double total = product.getPrice() * quantity *
                         (100.0 - discount) / 100.0;
    const int saleId = nextSaleId;
    sales.emplace_back(saleId, client, product, quantity, date, total);
    ++nextSaleId;
    return saleId;
}

int FurnitureShop::makeStoreOrder(const int storeId, const int productId,
                                  const int quantity, const std::string& date)
{
    const Store& store = getStore(storeId);
    return addSale(store, productId, quantity, store.getDiscount(), date);
}

int FurnitureShop::makeWholesaleSale(const int clientId, const int productId,
                                     const int quantity, const std::string& date)
{
    const WholesaleClient& client = getWholesaleClient(clientId);
    return addSale(client, productId, quantity, client.getDiscount(), date);
}

std::vector<Product*> FurnitureShop::getAvailableProducts() const
{
    std::vector<Product*> result;
    for (const auto& product : products)
    {
        if (product->getQuantity() > 0 || product->isMadeToOrder())
        {
            result.push_back(product.get());
        }
    }
    return result;
}

int FurnitureShop::getSoldQuantityForPeriod(const std::string& productName,
                                            const std::string& startDate,
                                            const std::string& endDate) const
{
    if (!isValidDate(startDate) || !isValidDate(endDate) || startDate > endDate)
    {
        throw std::invalid_argument("Неверный период");
    }

    int count = 0;
    for (const Sale& sale : sales)
    {
        if (sale.getProduct().getName() == productName &&
            sale.getDate() >= startDate && sale.getDate() <= endDate)
        {
            count += sale.getQuantity();
        }
    }
    return count;
}

std::vector<Sale> FurnitureShop::getOrdersForPeriod(const std::string& startDate,
                                                    const std::string& endDate) const
{
    if (!isValidDate(startDate) || !isValidDate(endDate) || startDate > endDate)
    {
        throw std::invalid_argument("Неверный период");
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

double FurnitureShop::calculateCustomOrderPrice(const double basePrice,
                                                const double markupPercent) const
{
    if (basePrice < 0 || markupPercent < 0)
    {
        throw std::invalid_argument("Цена/наценка < 0");
    }
    return basePrice * (1.0 + markupPercent / 100.0);
}

std::vector<std::string> FurnitureShop::getClientsWithDiscount() const
{
    std::vector<std::string> result;
    for (const Store& store : stores)
    {
        if (store.getDiscount() > 0)
        {
            result.push_back(store.getInfo());
        }
    }
    for (const WholesaleClient& client : wholesaleClients)
    {
        if (client.getDiscount() > 0)
        {
            result.push_back(client.getInfo());
        }
    }
    return result;
}
