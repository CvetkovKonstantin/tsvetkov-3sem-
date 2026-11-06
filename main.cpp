#include "Shop.h"

#include <functional>
#include <iostream>
#include <vector>

/**
 * @brief Демонстрационная работа мебельного магазина
 * @return 0 при успешном завершении программы
 */
int main()
{
    Shop shop("Мебель для дома");
    shop.addProduct(Product(1, "Стол обеденный", "Фабрика Стол", 12000, 10));
    shop.addProduct(Product(2, "Стул", "Фабрика Стол", 3500, 40));
    shop.addProduct(Product(3, "Шкаф купе", "Фабрика Мебель", 25000, 5));
    shop.addProduct(Product(4, "Диван", "Фабрика Диван", 40000, 0));

    const RetailClient buyer(1, "Иванов Иван", "+7 900 111-22-33");
    const RetailClient secondBuyer(2, "Петрова Анна", "+7 900 444-55-66");
    const DesignClient projectBuyer(3, "ООО Кухни", "ул. Ленина, 10", 20);
    const DesignClient secondProjectBuyer(4, "Сидоров Пётр", "ул. Мира, 5", 15);
    shop.addRetailClient(buyer);
    shop.addRetailClient(secondBuyer);
    shop.addDesignClient(projectBuyer);
    shop.addDesignClient(secondProjectBuyer);

    const std::vector<std::reference_wrapper<const Client>> clients =
    {
        std::cref(buyer), std::cref(secondBuyer),
        std::cref(projectBuyer), std::cref(secondProjectBuyer)
    };

    std::cout << "Клиенты мебельного магазина:\n";
    for (const Client& client : clients)
    {
        std::cout << client.getInfo() << '\n';
    }

    shop.makeSale(1, 1, 2, "2026-10-05");
    shop.makeSale(2, 2, 4, "2026-10-06");
    shop.makeSale(1, 1, 1, "2026-10-20");
    shop.makeCustomOrder(3, 3, 2, "2026-10-10");
    shop.makeCustomOrder(4, 2, 6, "2026-10-12");
    shop.receiveProduct(4, 3);

    std::cout << "\n1. Ассортимент и цены:\n";
    for (const Product& product : shop.getAvailableProducts())
    {
        std::cout << product.getInfo() << '\n';
    }

    std::cout << "\n2. Продано столов за 2026-10-01 - 2026-10-31: "
              << shop.getSoldQuantity(1, "2026-10-01", "2026-10-31")
              << " шт.\n";

    std::cout << "\n3. Продажи за 2026-10-01 - 2026-10-15:\n";
    for (const Sale& sale : shop.getSalesBetween("2026-10-01", "2026-10-15"))
    {
        std::cout << sale.getInfo() << '\n';
    }

    std::cout << "\n4. Заказы по индивидуальному проекту за 2026-10-01 - 2026-10-15:\n";
    for (const CustomOrder& order :
         shop.getOrdersBetween("2026-10-01", "2026-10-15"))
    {
        std::cout << order.getInfo() << '\n';
    }

    std::cout << "\n5. Стоимость заказа по проекту:\n";
    std::cout << "Клиент " << projectBuyer.getName() << ": "
              << shop.calculateOrderCost(1, 3, projectBuyer.getMarkupPercent())
              << " (надбавка " << projectBuyer.getMarkupPercent() << "%)\n";
    return 0;
}
