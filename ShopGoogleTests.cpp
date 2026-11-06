#include "Shop.h"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(ProductTests, ConstructorAndStock)
{
    Product product(1, "Стол", "Фабрика Стол", 12000, 10);
    EXPECT_EQ("Стол", product.getName());
    EXPECT_EQ(10, product.getQuantity());
    product.addQuantity(5);
    EXPECT_EQ(15, product.getQuantity());
    product.removeQuantity(5);
    EXPECT_EQ(10, product.getQuantity());
    EXPECT_THROW(product.removeQuantity(100), std::runtime_error);
}

TEST(ProductTests, InvalidData)
{
    EXPECT_THROW(Product(0, "Стол", "Фабрика", 100, 1), std::invalid_argument);
    EXPECT_THROW(Product(1, "", "Фабрика", 100, 1), std::invalid_argument);
    EXPECT_THROW(Product(1, "Стол", "", 100, 1), std::invalid_argument);
    EXPECT_THROW(Product(1, "Стол", "Фабрика", 0, 1), std::invalid_argument);
    EXPECT_THROW(Product(1, "Стол", "Фабрика", 100, -1), std::invalid_argument);
}

TEST(ClientTests, Polymorphism)
{
    const RetailClient retail(1, "Иванов", "+7 900 111-22-33");
    const DesignClient design(2, "Кухни", "ул. Мира, 5", 20);
    const Client& first = retail;
    const Client& second = design;
    EXPECT_NE(std::string::npos, first.getInfo().find("Розничный покупатель:"));
    EXPECT_NE(std::string::npos, second.getInfo().find("Клиент проекта:"));
}

TEST(ClientTests, InvalidData)
{
    EXPECT_THROW(RetailClient(1, "Иванов", ""), std::invalid_argument);
    EXPECT_THROW(DesignClient(1, "Кухни", "", 20), std::invalid_argument);
    EXPECT_THROW(DesignClient(1, "Кухни", "ул. Мира, 5", -5), std::invalid_argument);
}

class ShopTests : public ::testing::Test
{
protected:
    Shop shop{"Мебель"};

    void SetUp() override
    {
        shop.addProduct(Product(1, "Стол", "Фабрика Стол", 12000, 10));
        shop.addProduct(Product(2, "Стул", "Фабрика Стол", 3500, 40));
        shop.addProduct(Product(3, "Шкаф", "Фабрика Мебель", 25000, 0));
        shop.addRetailClient(RetailClient(1, "Иванов", "+7 900 111-22-33"));
        shop.addRetailClient(RetailClient(2, "Петрова", "+7 900 444-55-66"));
        shop.addDesignClient(DesignClient(3, "Кухни", "ул. Ленина, 10", 20));
    }
};

TEST_F(ShopTests, AvailableProducts)
{
    EXPECT_EQ(2u, shop.getAvailableProducts().size());
    shop.receiveProduct(3, 4);
    EXPECT_EQ(3u, shop.getAvailableProducts().size());
    EXPECT_EQ(4, shop.getProduct(3).getQuantity());
}

TEST_F(ShopTests, SaleDecreasesStock)
{
    shop.makeSale(1, 1, 2, "2026-10-05");
    EXPECT_EQ(8, shop.getProduct(1).getQuantity());
    EXPECT_EQ(2, shop.getAllSales().at(0).getQuantity());
    EXPECT_DOUBLE_EQ(24000.0, shop.getAllSales().at(0).getTotal());
}

TEST_F(ShopTests, SoldQuantityForPeriod)
{
    shop.makeSale(1, 1, 2, "2026-10-05");
    shop.makeSale(2, 1, 1, "2026-10-20");
    shop.makeSale(1, 1, 1, "2026-11-02");
    EXPECT_EQ(3, shop.getSoldQuantity(1, "2026-10-01", "2026-10-31"));
    EXPECT_EQ(2, shop.getSoldQuantity(1, "2026-10-01", "2026-10-10"));
    EXPECT_EQ(0, shop.getSoldQuantity(2, "2026-10-01", "2026-10-31"));
}

TEST_F(ShopTests, SalesBetweenDates)
{
    shop.makeSale(1, 1, 1, "2026-10-05");
    shop.makeSale(2, 2, 1, "2026-10-10");
    shop.makeSale(1, 2, 1, "2026-10-25");
    EXPECT_EQ(2u, shop.getSalesBetween("2026-10-05", "2026-10-10").size());
    EXPECT_EQ(3u, shop.getSalesBetween("2026-10-01", "2026-10-31").size());
    EXPECT_THROW(shop.getSalesBetween("2026-10-30", "2026-10-01"),
                 std::invalid_argument);
}

TEST_F(ShopTests, CustomOrderCostWithMarkup)
{
    EXPECT_DOUBLE_EQ(14400.0, shop.calculateOrderCost(1, 1, 20.0));
    EXPECT_DOUBLE_EQ(24000.0, shop.calculateOrderCost(1, 2, 0.0));
    EXPECT_THROW(shop.calculateOrderCost(1, 0, 20.0), std::invalid_argument);
    EXPECT_THROW(shop.calculateOrderCost(1, 1, -1), std::invalid_argument);
}

TEST_F(ShopTests, CustomOrdersBetweenDates)
{
    EXPECT_DOUBLE_EQ(28800.0, shop.makeCustomOrder(3, 1, 2, "2026-10-10"));
    EXPECT_DOUBLE_EQ(4200.0, shop.makeCustomOrder(3, 2, 1, "2026-10-12"));
    shop.makeCustomOrder(3, 1, 1, "2026-11-01");

    const std::vector<CustomOrder> orders =
        shop.getOrdersBetween("2026-10-01", "2026-10-31");
    EXPECT_EQ(2u, orders.size());
    EXPECT_EQ(20.0, orders.at(0).getMarkupPercent());
    EXPECT_EQ(3u, shop.getAllOrders().size());
    EXPECT_THROW(shop.getOrdersBetween("2026-11-30", "2026-11-01"),
                 std::invalid_argument);
}

TEST_F(ShopTests, NotEnoughStock)
{
    EXPECT_THROW(shop.makeSale(1, 1, 50, "2026-10-05"), std::runtime_error);
    EXPECT_THROW(shop.makeSale(1, 3, 1, "2026-10-05"), std::runtime_error);
    EXPECT_EQ(10, shop.getProduct(1).getQuantity());
    EXPECT_TRUE(shop.getAllSales().empty());
}

TEST_F(ShopTests, InvalidDateAndDuplicateIds)
{
    EXPECT_THROW(shop.makeSale(1, 1, 1, "2026-02-29"), std::invalid_argument);
    EXPECT_THROW(shop.makeSale(1, 1, 1, "05.10.2026"), std::invalid_argument);
    EXPECT_THROW(shop.addProduct(Product(1, "Иной", "Фабрика", 1, 1)),
                 std::invalid_argument);
    EXPECT_THROW(shop.addRetailClient(RetailClient(3, "Другой", "+7 900 000-00-00")),
                 std::invalid_argument);
    EXPECT_THROW(shop.getRetailClient(99), std::invalid_argument);
    EXPECT_THROW(shop.getDesignClient(99), std::invalid_argument);
}
