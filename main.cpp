#include "FurnitureShop.h"
#include "Furniture.h"
#include "CustomOrder.h"

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Точка входа демонстрационной программы
 * @return 0 при успешном завершении
 */
int main()
{
    FurnitureShop shop("Мебельный мир");

    shop.addProduct(std::make_unique<Furniture>(1, "Шкаф", "Корпусная", 25000, 10));
    shop.addProduct(std::make_unique<Furniture>(2, "Диван", "Мягкая", 40000, 5));
    shop.addProduct(std::make_unique<CustomOrder>(3, "Кухня на заказ", "Кухня", 80000, 15));

    const Store store(1, "Гостиный двор", 5, "ул. Ленина, 10");
    const WholesaleClient buyer(3, "ОптТорг", 10, "Иван Петров");
    shop.addStore(store);
    shop.addWholesaleClient(buyer);

    const std::vector<std::reference_wrapper<const Client>> clients =
    {
        std::cref(store), std::cref(buyer)
    };

    std::cout << "Клиенты магазина:\n";
    for (const Client& client : clients)
    {
        std::cout << client.getInfo() << '\n';
    }

    shop.makeStoreOrder(1, 1, 2, "2026-10-20");
    shop.makeWholesaleSale(3, 2, 1, "2026-10-21");
    shop.makeStoreOrder(1, 3, 1, "2026-10-22");

    std::cout << "\n1. Ассортимент в наличии и цена:\n";
    for (const Product* product : shop.getAvailableProducts())
    {
        std::cout << product->getInfo() << '\n';
    }

    std::cout << "\n2. Количество проданного 'Шкаф' за период:\n";
    std::cout << "Продано: "
              << shop.getSoldQuantityForPeriod("Шкаф", "2026-10-20", "2026-10-22")
              << " шт.\n";

    std::cout << "\n3. Список заказов за период:\n";
    for (const Sale& sale : shop.getOrdersForPeriod("2026-10-20", "2026-10-22"))
    {
        std::cout << sale.getInfo() << '\n';
    }

    std::cout << "\n4. Расчет индивидуального заказа:\n";
    std::cout << "Стоимость кухни (база 80000, наценка 15%): "
              << shop.calculateCustomOrderPrice(80000, 15) << " руб.\n";

    std::cout << "\n5. Клиенты со скидкой:\n";
    for (const std::string& info : shop.getClientsWithDiscount())
    {
        std::cout << info << '\n';
    }

    return 0;
}
