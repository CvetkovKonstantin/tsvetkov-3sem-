#include "FurnitureShop.h"
#include "Furniture.h"
#include "CustomOrder.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(ProductTests, FurnitureAndCustomOrder) {
    Furniture f(1, "Шкаф", "Корпусная", 10000, 10);
    EXPECT_EQ(10000, f.getPrice());
    
    CustomOrder c(2, "Кухня", "Кухня", 50000, 20);
    EXPECT_EQ(60000, c.getPrice()); // 50000 + 20%
}

TEST(SaleTests, ValidConstruction) {
    Store store(10, "Магазин", 5, "ул. Мира");
    Furniture product(20, "Стол", "Корпусная", 5000, 10);
    Sale sale(1, store, product, 2, "2026-10-20", 9500);
    EXPECT_EQ(10, sale.getClientId());
    EXPECT_EQ(20, sale.getProductId());
}

class ShopTests : public ::testing::Test {
protected:
    FurnitureShop shop{"Тест"};
    void SetUp() override {
        shop.addProduct(new Furniture(100, "Шкаф", "Корпусная", 10000, 10));
        shop.addProduct(new CustomOrder(101, "Кухня", "Кухня", 50000, 15));
        shop.addStore(Store(200, "Магазин А", 5, "ул. Мира"));
    }
};

TEST_F(ShopTests, Task2_SoldQuantityForPeriod) {
    shop.makeStoreOrder(200, 100, 2, "2026-10-20");
    shop.makeStoreOrder(200, 100, 3, "2026-10-22");
    // Продано за 20-21 октября
    EXPECT_EQ(2, shop.getSoldQuantityForPeriod("Шкаф", "2026-10-20", "2026-10-21"));
}

TEST_F(ShopTests, Task3_OrdersForPeriod) {
    shop.makeStoreOrder(200, 100, 2, "2026-10-20");
    shop.makeStoreOrder(200, 100, 3, "2026-10-22");
    EXPECT_EQ(1, shop.getOrdersForPeriod("2026-10-20", "2026-10-21").size());
}

TEST_F(ShopTests, Task4_CalculateCustomOrder) {
    EXPECT_DOUBLE_EQ(57500.0, shop.calculateCustomOrderPrice(50000, 15));
}

TEST_F(ShopTests, CustomOrderDoesNotAffectStock) {
    // Индивидуальный заказ не должен требовать остатка на складе
    EXPECT_NO_THROW(shop.makeStoreOrder(200, 101, 1, "2026-10-20"));
}
