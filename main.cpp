#include "FurnitureShop.h"
#include "Furniture.h"
#include "CustomOrder.h"
#include <iostream>
#include <vector>

/**
 * @brief Точка входа демонстрационной программы
 * @return 0 при успешном завершении
 */
int main()
{
    FurnitureShop shop("Мебельный мир");
    
    // Создаем коллекцию базового типа и заполняем наследниками 
    std::vector<Product*> catalog;
    catalog.push_back(new Furniture(1, "Шкаф", "Корпусная", 25000, 10));
    catalog.push_back(new Furniture(2, "Диван", "Мягкая", 40000, 5));
    catalog.push_back(new CustomOrder(3, "Кухня на заказ", "Кухня", 80000, 15));

    for (Product* p : catalog) shop.addProduct(p);

    const Store store(1, "Гостиный двор", 5, "ул. Ленина, 10");
    const WholesaleClient buyer(3, "ОптТорг", 10, "Иван Петров");
    shop.addStore(store);
    shop.addWholesaleClient(buyer);

    std::cout << "=== Полный каталог  ===\n";
    for (const Product* p : catalog) {
        std::cout << p->getInfo() << '\n';
    }

    shop.makeStoreOrder(1, 1, 2, "2026-10-20");
    shop.makeWholesaleSale(3, 2, 1, "2026-10-21");
    shop.makeStoreOrder(1, 3, 1, "2026-10-22"); // Заказ индивидуального проекта

    std::cout << "\n=== 1. Ассортимент в наличии и цена ===\n";
    for (const Product* p : shop.getAvailableProducts()) {
        std::cout << p->getInfo() << '\n';
    }

    std::cout << "\n=== 2. Количество проданного 'Шкаф' за период ===\n";
    std::cout << "Продано: " << shop.getSoldQuantityForPeriod("Шкаф", "2026-10-20", "2026-10-22") << " шт.\n";

    std::cout << "\n=== 3. Список заказов за период ===\n";
    for (const Sale& s : shop.getOrdersForPeriod("2026-10-20", "2026-10-22")) {
        std::cout << s.getInfo() << '\n';
    }

    std::cout << "\n=== 4. Расчет индивидуального заказа ===\n";
    std::cout << "Стоимость кухни (база 80000, наценка 15%): " 
              << shop.calculateCustomOrderPrice(80000, 15) << " руб.\n";

    return 0;
}
