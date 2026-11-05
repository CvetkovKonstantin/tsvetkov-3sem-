#include "FurnitureShop.h"
#include "Furniture.h"
#include "CustomOrder.h"

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

TEST(ProductTests, FurnitureAndCustomOrder)
{
    const Furniture furniture(1, "Шкаф", "Корпусная", 10000, 10);
    EXPECT_EQ(10000, furniture.getPrice());
    EXPECT_FALSE(furniture.isMadeToOrder());

    const CustomOrder custom(2, "Кухня", "Кухня", 50000, 20);
    EXPECT_EQ(60000, custom.getPrice());
    EXPECT_TRUE(custom.isMadeToOrder());
}

TEST(ProductTests, InvalidData)
{
    EXPECT_THROW(Furniture(0, "Шкаф", "Корпусная", 10000, 10), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "", "Корпусная", 10000, 10), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "Шкаф", "", 10000, 10), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "Шкаф", "Корпусная", -1, 10), std::invalid_argument);
    EXPECT_THROW(Furniture(1, "Шкаф", "Корпусная", 10000, -1), std::invalid_argument);
    EXPECT_THROW(CustomOrder(2, "Кухня", "Кухня", -1, 20), std::invalid_argument);
    EXPECT_THROW(CustomOrder(2, "Кухня", "Кухня", 50000, -1), std::invalid_argument);
}

TEST(ClientTests, Polymorphism)
{
    const Store store(1, "Гостиный двор", 5, "ул. Ленина, 10");
    const WholesaleClient wholesale(2, "ОптТорг", 10, "Иван Петров");
    const Client& first = store;
    const Client& second = wholesale;
    EXPECT_NE(std::string::npos, first.getInfo().find("Магазин:"));
    EXPECT_NE(std::string::npos, second.getInfo().find("Оптовик:"));
}

class ShopTests : public ::testing::Test
{
protected:
    FurnitureShop shop{"Тест"};

    void SetUp() override
    {
        shop.addProduct(std::make_unique<Furniture>(100, "Шкаф", "Корпусная", 10000, 10));
        shop.addProduct(std::make_unique<Furniture>(102, "Диван", "Мягкая", 40000, 5));
        shop.addProduct(std::make_unique<CustomOrder>(101, "Кухня", "Кухня", 50000, 15));
        shop.addStore(Store(200, "Магазин А", 5, "ул. Мира"));
        shop.addStore(Store(201, "Магазин Б", 0, "ул. Ленина"));
        shop.addWholesaleClient(WholesaleClient(300, "ОптТорг", 10, "Иван Петров"));
    }
};

TEST_F(ShopTests, Task1_AvailableProducts)
{
    EXPECT_EQ(3u, shop.getAvailableProducts().size());

    // Индивидуальный заказ доступен всегда, даже при нулевом остатке
    const CustomOrder& custom = dynamic_cast<const CustomOrder&>(shop.getProduct(101));
    EXPECT_EQ(0, custom.getQuantity());
}

TEST_F(ShopTests, Task2_SoldQuantityForPeriod)
{
    shop.makeStoreOrder(200, 100, 2, "2026-10-20");
    shop.makeStoreOrder(200, 100, 3, "2026-10-22");
    EXPECT_EQ(2, shop.getSoldQuantityForPeriod("Шкаф", "2026-10-20", "2026-10-21"));
    EXPECT_EQ(5, shop.getSoldQuantityForPeriod("Шкаф", "2026-10-20", "2026-10-22"));
}

TEST_F(ShopTests, Task3_OrdersForPeriod)
{
    shop.makeStoreOrder(200, 100, 2, "2026-10-20");
    shop.makeStoreOrder(200, 100, 3, "2026-10-22");
    EXPECT_EQ(1u, shop.getOrdersForPeriod("2026-10-20", "2026-10-21").size());
    EXPECT_EQ(2u, shop.getOrdersForPeriod("2026-10-20", "2026-10-22").size());
    EXPECT_THROW(shop.getOrdersForPeriod("2026-10-30", "2026-10-01"), std::invalid_argument);
}

TEST_F(ShopTests, Task4_CalculateCustomOrder)
{
    EXPECT_DOUBLE_EQ(57500.0, shop.calculateCustomOrderPrice(50000, 15));
    EXPECT_DOUBLE_EQ(50000.0, shop.calculateCustomOrderPrice(50000, 0));
    EXPECT_THROW(shop.calculateCustomOrderPrice(-1, 15), std::invalid_argument);
    EXPECT_THROW(shop.calculateCustomOrderPrice(50000, -1), std::invalid_argument);
}

TEST_F(ShopTests, CustomOrderDoesNotAffectStock)
{
    // Индивидуальный заказ не должен требовать остатка на складе
    EXPECT_NO_THROW(shop.makeStoreOrder(200, 101, 1, "2026-10-20"));
    EXPECT_EQ(0, shop.getProduct(101).getQuantity());
}

TEST_F(ShopTests, DiscountClients)
{
    EXPECT_EQ(2u, shop.getClientsWithDiscount().size());
}

TEST_F(ShopTests, NotEnoughStock)
{
    EXPECT_THROW(shop.makeStoreOrder(200, 100, 50, "2026-10-20"), std::runtime_error);
    EXPECT_EQ(10, shop.getProduct(100).getQuantity());
    EXPECT_TRUE(shop.getAllSales().empty());
}

TEST_F(ShopTests, InvalidDateAndDuplicateIds)
{
    EXPECT_THROW(shop.makeStoreOrder(200, 100, 1, "2026-02-29"), std::invalid_argument);
    EXPECT_THROW(shop.addProduct(std::make_unique<Furniture>(100, "Иной", "Корпусная", 1, 1)),
                 std::invalid_argument);
    EXPECT_THROW(shop.addStore(Store(300, "Другой", 0, "ул. Мира")),
                 std::invalid_argument);
}

TEST_F(ShopTests, WholesaleSaleAndDiscount)
{
    const int saleId = shop.makeWholesaleSale(300, 102, 2, "2026-10-21");
    EXPECT_EQ(1, saleId);
    EXPECT_EQ(3, shop.getProduct(102).getQuantity());
    // 40000 * 2 * (100 - 10) / 100 = 72000
    EXPECT_DOUBLE_EQ(72000.0, shop.getAllSales().at(0).getTotal());
}
