#include "FurnitureShop.h"
#include "Furniture.h"
#include "CustomOrder.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <type_traits>


TEST(ProductTests, DefaultProperties) {
    Furniture f(1, "Шкаф", "Корпусная", 15000.0, 5);
    EXPECT_EQ(f.getId(), 1);
    EXPECT_EQ(f.getName(), "Шкаф");
    EXPECT_EQ(f.getCategory(), "Корпусная");
    EXPECT_DOUBLE_EQ(f.getPrice(), 15000.0);
    EXPECT_EQ(f.getQuantity(), 5);
}

TEST(ProductTests, InvalidDataThrows) {
    EXPECT_THROW(Furniture(0, "Шкаф", "Корпусная", 15000.0, 5), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "", "Корпусная", 15000.0, 5), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "Шкаф", "", 15000.0, 5), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "Шкаф", "Корпусная", -100.0, 5), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "Шкаф", "Корпусная", 15000.0, -1), std::invalid_argument);
}

TEST(ProductTests, QuantityManagement) {
    Furniture f(1, "Шкаф", "Корпусная", 15000.0, 10);
    
    f.addQuantity(5);
    EXPECT_EQ(f.getQuantity(), 15);
    
    f.removeQuantity(3);
    EXPECT_EQ(f.getQuantity(), 12);
    
    EXPECT_THROW(f.addQuantity(0), std::invalid_argument);
    EXPECT_THROW(f.removeQuantity(0), std::invalid_argument);
    EXPECT_THROW(f.removeQuantity(100), std::runtime_error);
}

TEST(ProductTests, UniqueIds) {
    Furniture f1(100, "Шкаф", "Корпусная", 15000.0, 10);
    // Попытка создать товар с существующим ID должна выбросить исключение
    EXPECT_THROW(Furniture(100, "Стол", "Корпусная", 5000.0, 5), std::invalid_argument);
}

TEST(CustomOrderTests, PriceCalculation) {
    CustomOrder c(1, "Кухня", "Кухня", 50000.0, 20.0);
    EXPECT_DOUBLE_EQ(c.getBasePrice(), 50000.0);
    EXPECT_DOUBLE_EQ(c.getMarkupPercent(), 20.0);
    EXPECT_DOUBLE_EQ(c.getPrice(), 60000.0); // 50000 + 20%
    EXPECT_EQ(c.getQuantity(), 0);           // Всегда 0, так как делается на заказ
}

TEST(CustomOrderTests, InvalidMarkupThrows) {
    EXPECT_THROW(CustomOrder(1, "Кухня", "Кухня", 50000.0, -5.0), std::invalid_argument);
}



TEST(ClientTests, StoreProperties) {
    Store s(1, "Гостиный двор", 10.0, "ул. Ленина, 10");
    EXPECT_EQ(s.getId(), 1);
    EXPECT_EQ(s.getName(), "Гостиный двор");
    EXPECT_DOUBLE_EQ(s.getDiscount(), 10.0);
    EXPECT_EQ(s.getAddress(), "ул. Ленина, 10");
}

TEST(ClientTests, WholesaleClientProperties) {
    WholesaleClient w(2, "ОптТорг", 5.0, "Иван Петров");
    EXPECT_EQ(w.getId(), 2);
    EXPECT_EQ(w.getName(), "ОптТорг");
    EXPECT_DOUBLE_EQ(w.getDiscount(), 5.0);
    EXPECT_EQ(w.getContactPerson(), "Иван Петров");
}

TEST(ClientTests, InvalidClientDataThrows) {
    EXPECT_THROW(Store(0, "Магазин", 5, "Адрес"), std::invalid_argument);
    EXPECT_THROW(Store(1, "", 5, "Адрес"), std::invalid_argument);
    EXPECT_THROW(Store(1, "Магазин", -5, "Адрес"), std::invalid_argument);
    EXPECT_THROW(Store(1, "Магазин", 105, "Адрес"), std::invalid_argument);
    EXPECT_THROW(Store(1, "Магазин", 5, ""), std::invalid_argument);
    
    EXPECT_THROW(WholesaleClient(1, "Опт", 5, ""), std::invalid_argument);
}

TEST(ClientTests, Polymorphism) {
    Store store(1, "Магазин", 5, "ул. Мира");
    WholesaleClient wholesale(2, "Оптовик", 10, "Анна");
    
    // Использование как базового типа
    const Client& c1 = store;
    const Client& c2 = wholesale;
    
    EXPECT_NE(c1.getInfo().find("Магазин:"), std::string::npos);
    EXPECT_NE(c2.getInfo().find("Оптовик:"), std::string::npos);
}


TEST(SaleTests, ValidConstruction) {
    Store store(10, "Магазин", 5, "ул. Мира");
    Furniture product(20, "Стол", "Корпусная", 5000, 10);
    Sale sale(1, store, product, 2, "2026-10-20", 9500.0);
    
    EXPECT_EQ(sale.getId(), 1);
    EXPECT_EQ(sale.getClientId(), 10);
    EXPECT_EQ(sale.getProductId(), 20);
    EXPECT_EQ(sale.getQuantity(), 2);
    EXPECT_EQ(sale.getDate(), "2026-10-20");
    EXPECT_DOUBLE_EQ(sale.getTotal(), 9500.0);
}

TEST(SaleTests, InvalidDataThrows) {
    Store store(10, "Магазин", 5, "ул. Мира");
    Furniture product(20, "Стол", "Корпусная", 5000, 10);
    
    EXPECT_THROW(Sale(0, store, product, 2, "2026-10-20", 9500), std::invalid_argument);
    EXPECT_THROW(Sale(1, store, product, 0, "2026-10-20", 9500), std::invalid_argument);
    EXPECT_THROW(Sale(1, store, product, 2, "", 9500), std::invalid_argument);
    EXPECT_THROW(Sale(1, store, product, 2, "2026-10-20", -100), std::invalid_argument);
}


class ShopTest : public ::testing::Test {
protected:
    FurnitureShop* shop;

    void SetUp() override {
        shop = new FurnitureShop("Тестовый магазин");
        
        // Товары (ID: 100, 101)
        shop->addProduct(new Furniture(100, "Шкаф", "Корпусная", 10000.0, 10));
        shop->addProduct(new CustomOrder(101, "Кухня", "Кухня", 50000.0, 20.0)); // Цена: 60000
        
        // Клиенты (ID: 1, 2)
        shop->addStore(Store(1, "Магазин А", 10.0, "ул. Мира")); // Скидка 10%
        shop->addWholesaleClient(WholesaleClient(2, "Опт", 0.0, "Анна")); // Без скидки
    }

    void TearDown() override {
        delete shop;
    }
};

TEST_F(ShopTest, AddUniqueEntities) {
    // Попытка добавить товар с дубликатом ID
    EXPECT_THROW(shop->addProduct(new Furniture(100, "Другой", "Кат", 100.0, 1)), std::invalid_argument);
    
    // Попытка добавить магазин с дубликатом ID
    EXPECT_THROW(shop->addStore(Store(1, "Другой", 0, "Адрес")), std::invalid_argument);
    
    // Попытка занять ID магазина оптовиком
    EXPECT_THROW(shop->addWholesaleClient(WholesaleClient(1, "Опт2", 0, "Петр")), std::invalid_argument);
}

TEST_F(ShopTest, MakeStoreOrderWithDiscount) {
    // Продаем 2 шкафа магазину (скидка 10%)
    // 10000 * 2 = 20000. Скидка 10% -> 18000.
    shop->makeStoreOrder(1, 100, 2, "2026-10-20");
    
    EXPECT_EQ(shop->getProduct(100).getQuantity(), 8); // Остаток уменьшился
    EXPECT_EQ(shop->getAllSales().size(), 1);
    EXPECT_DOUBLE_EQ(shop->getAllSales()[0].getTotal(), 18000.0);
}

TEST_F(ShopTest, MakeWholesaleSaleWithoutDiscount) {
    // Продаем 1 кухню оптовику (скидка 0%)
    // Цена кухни: 60000.
    shop->makeWholesaleSale(2, 101, 1, "2026-10-21");
    
    // Кухня на заказ, у нее не списывается остаток
    EXPECT_EQ(shop->getProduct(101).getQuantity(), 0);
    EXPECT_EQ(shop->getAllSales().size(), 1);
    EXPECT_DOUBLE_EQ(shop->getAllSales()[0].getTotal(), 60000.0);
}

TEST_F(ShopTest, NotEnoughStockThrows) {
    // Просим 20 шкафов, а есть только 10
    EXPECT_THROW(shop->makeStoreOrder(1, 100, 20, "2026-10-20"), std::runtime_error);
    
    // Проверяем, что остаток не изменился
    EXPECT_EQ(shop->getProduct(100).getQuantity(), 10);
    EXPECT_TRUE(shop->getAllSales().empty());
}

TEST_F(ShopTest, Task1_GetAvailableProducts) {
    // Изначально доступны оба товара (шкафов 10, кухня под заказ)
    auto available = shop->getAvailableProducts();
    EXPECT_EQ(available.size(), 2);
    
    // Продаем все шкафы
    shop->makeStoreOrder(1, 100, 10, "2026-10-20");
    
    // Теперь шкафов нет, но кухня все еще доступна (она делается на заказ)
    available = shop->getAvailableProducts();
    EXPECT_EQ(available.size(), 1);
    EXPECT_EQ(available[0]->getId(), 101);
}

TEST_F(ShopTest, Task2_SoldQuantityForPeriod) {
    shop->makeStoreOrder(1, 100, 2, "2026-10-01");
    shop->makeStoreOrder(1, 100, 3, "2026-10-15");
    shop->makeStoreOrder(1, 100, 1, "2026-11-01"); // Вне периода
    
    // Ищем за октябрь
    int qty = shop->getSoldQuantityForPeriod("Шкаф", "2026-10-01", "2026-10-31");
    EXPECT_EQ(qty, 5); // 2 + 3
    
    // Неверный период
    EXPECT_THROW(shop->getSoldQuantityForPeriod("Шкаф", "2026-11-01", "2026-10-01"), std::invalid_argument);
}

TEST_F(ShopTest, Task3_GetOrdersForPeriod) {
    shop->makeStoreOrder(1, 100, 2, "2026-10-01");
    shop->makeStoreOrder(1, 100, 3, "2026-10-15");
    shop->makeStoreOrder(1, 100, 1, "2026-11-01");
    
    auto orders = shop->getOrdersForPeriod("2026-10-01", "2026-10-31");
    EXPECT_EQ(orders.size(), 2); // Должны попасть только две продажи
}

TEST_F(ShopTest, Task4_CalculateCustomOrderPrice) {
    // Базовая цена 50000, наценка 15% = 57500
    EXPECT_DOUBLE_EQ(shop->calculateCustomOrderPrice(50000, 15), 57500.0);
    
    // Базовая цена 10000, наценка 0% = 10000
    EXPECT_DOUBLE_EQ(shop->calculateCustomOrderPrice(10000, 0), 10000.0);
    
    EXPECT_THROW(shop->calculateCustomOrderPrice(-100, 10), std::invalid_argument);
}

TEST_F(ShopTest, InvalidDateThrows) {
    EXPECT_THROW(shop->makeStoreOrder(1, 100, 1, "2026-13-01"), std::invalid_argument);
    EXPECT_THROW(shop->makeStoreOrder(1, 100, 1, "2026-02-30"), std::invalid_argument);
    EXPECT_THROW(shop->makeStoreOrder(1, 100, 1, "20-10-2026"), std::invalid_argument);
}

// Проверка того, что магазин защищен от копирования (правило трёх)
TEST_F(ShopTest, IsNotCopyable) {
    EXPECT_FALSE(std::is_copy_constructible<FurnitureShop>::value);
    EXPECT_FALSE(std::is_copy_assignable<FurnitureShop>::value);
}
