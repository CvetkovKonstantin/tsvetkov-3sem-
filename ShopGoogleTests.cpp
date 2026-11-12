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

TEST(ProductTests, UniqueId)
{
    const Product product(600, "Стол", "Фабрика", 100, 5);
    EXPECT_EQ(600, product.getId());
    EXPECT_THROW(Product(600, "Стул", "Фабрика", 100, 5), std::invalid_argument);
    const Product copy(product);
    EXPECT_EQ(product.getId(), copy.getId());
}

TEST(ProductTests, AutomaticId)
{
    const Product first("Стол", "Фабрика", 100, 5);
    const Product second("Стул", "Фабрика", 100, 5);
    EXPECT_TRUE(first.getId() > 0);
    EXPECT_NE(first.getId(), second.getId());
}

TEST(ClientTests, Polymorphism)
{
    const RetailClient retail("Иванов", "+7 900 111-22-33");
    const DesignClient design("Кухни", "ул. Мира, 5", 20);
    const Client& first = retail;
    const Client& second = design;
    EXPECT_NE(std::string::npos, first.getInfo().find("Розничный покупатель:"));
    EXPECT_NE(std::string::npos, second.getInfo().find("Клиент проекта:"));
}

TEST(ClientTests, UniqueId)
{
    const RetailClient retail(100, "Иванов", "+7 900 111-22-33");
    EXPECT_THROW(RetailClient(100, "Петров", "+7 900 444-55-66"),
                 std::invalid_argument);
    EXPECT_THROW(DesignClient(100, "Кухни", "ул. Мира, 5", 20),
                 std::invalid_argument);
    EXPECT_NE(retail.getId(), 0);
}

TEST(ClientTests, AutomaticId)
{
    const RetailClient retail("Иванов", "+7 900 111-22-33");
    const DesignClient design("Кухни", "ул. Мира, 5", 20);
    const RetailClient next("Петров", "+7 900 444-55-66");
    EXPECT_TRUE(retail.getId() > 0);
    EXPECT_LT(retail.getId(), design.getId());
    EXPECT_LT(design.getId(), next.getId());
}

TEST(ClientTests, InvalidData)
{
    EXPECT_THROW(RetailClient(300, "Иванов", ""), std::invalid_argument);
    EXPECT_THROW(DesignClient(301, "Кухни", "", 20), std::invalid_argument);
    EXPECT_THROW(DesignClient(302, "Кухни", "ул. Мира, 5", -5), std::invalid_argument);
}

TEST(SaleTests, UniqueId)
{
    const RetailClient buyer(200, "Иванов", "+7 900 111-22-33");
    const Product product(201, "Стол", "Фабрика", 12000, 10);
    const Sale sale(700, buyer, product, 1, "2026-10-05", 12000);
    EXPECT_EQ(700, sale.getId());
    EXPECT_THROW(Sale(700, buyer, product, 1, "2026-10-05", 12000),
                 std::invalid_argument);

    const CustomOrder order(701, buyer, product, 1, "2026-10-06", 14400, 20);
    EXPECT_EQ(701, order.getId());
    EXPECT_THROW(CustomOrder(701, buyer, product, 1, "2026-10-06", 14400, 20),
                 std::invalid_argument);
}

TEST(SaleTests, AutomaticId)
{
    const RetailClient buyer(201, "Иванов", "+7 900 111-22-33");
    const Product product(202, "Стол", "Фабрика", 12000, 10);
    const Sale first(buyer, product, 1, "2026-10-05", 12000);
    const Sale second(buyer, product, 2, "2026-10-06", 24000);
    const CustomOrder order(buyer, product, 1, "2026-10-07", 14400, 20);
    EXPECT_TRUE(first.getId() > 0);
    EXPECT_NE(first.getId(), second.getId());
    EXPECT_NE(second.getId(), order.getId());
}

class ShopTests : public ::testing::Test
{
protected:
    Shop shop{"Мебель"};
    int tableId = 0;
    int chairId = 0;
    int wardrobeId = 0;
    int buyerId = 0;
    int secondBuyerId = 0;
    int projectBuyerId = 0;

    void SetUp() override
    {
        tableId = shop.addProduct(Product("Стол", "Фабрика Стол", 12000, 10));
        chairId = shop.addProduct(Product("Стул", "Фабрика Стол", 3500, 40));
        wardrobeId = shop.addProduct(Product("Шкаф", "Фабрика Мебель", 25000, 0));
        buyerId = shop.addRetailClient(
            RetailClient("Иванов", "+7 900 111-22-33"));
        secondBuyerId = shop.addRetailClient(
            RetailClient("Петрова", "+7 900 444-55-66"));
        projectBuyerId = shop.addDesignClient(
            DesignClient("Кухни", "ул. Ленина, 10", 20));
    }
};

TEST_F(ShopTests, AvailableProducts)
{
    EXPECT_EQ(2u, shop.getAvailableProducts().size());
    shop.receiveProduct(wardrobeId, 4);
    EXPECT_EQ(3u, shop.getAvailableProducts().size());
    EXPECT_EQ(4, shop.getProduct(wardrobeId).getQuantity());
}

TEST_F(ShopTests, AutomaticIds)
{
    EXPECT_TRUE(tableId > 0);
    EXPECT_LT(tableId, chairId);
    EXPECT_LT(chairId, wardrobeId);
    EXPECT_LT(buyerId, secondBuyerId);
    EXPECT_LT(secondBuyerId, projectBuyerId);
    EXPECT_EQ(tableId, shop.getProduct(tableId).getId());
    EXPECT_EQ(buyerId, shop.getRetailClient(buyerId).getId());
    EXPECT_EQ(projectBuyerId, shop.getDesignClient(projectBuyerId).getId());
}

TEST_F(ShopTests, SaleDecreasesStock)
{
    shop.makeSale(buyerId, tableId, 2, "2026-10-05");
    EXPECT_EQ(8, shop.getProduct(tableId).getQuantity());
    EXPECT_EQ(2, shop.getAllSales().at(0).getQuantity());
    EXPECT_DOUBLE_EQ(24000.0, shop.getAllSales().at(0).getTotal());
    EXPECT_EQ(buyerId, shop.getAllSales().at(0).getClientId());
}

TEST_F(ShopTests, SoldQuantityForPeriod)
{
    shop.makeSale(buyerId, tableId, 2, "2026-10-05");
    shop.makeSale(secondBuyerId, tableId, 1, "2026-10-20");
    shop.makeSale(buyerId, tableId, 1, "2026-11-02");
    EXPECT_EQ(3, shop.getSoldQuantity(tableId, "2026-10-01", "2026-10-31"));
    EXPECT_EQ(2, shop.getSoldQuantity(tableId, "2026-10-01", "2026-10-10"));
    EXPECT_EQ(0, shop.getSoldQuantity(chairId, "2026-10-01", "2026-10-31"));
}

TEST_F(ShopTests, SalesBetweenDates)
{
    shop.makeSale(buyerId, tableId, 1, "2026-10-05");
    shop.makeSale(secondBuyerId, chairId, 1, "2026-10-10");
    shop.makeSale(buyerId, chairId, 1, "2026-10-25");
    EXPECT_EQ(2u, shop.getSalesBetween("2026-10-05", "2026-10-10").size());
    EXPECT_EQ(3u, shop.getSalesBetween("2026-10-01", "2026-10-31").size());
    EXPECT_THROW(shop.getSalesBetween("2026-10-30", "2026-10-01"),
                 std::invalid_argument);
}

TEST_F(ShopTests, CustomOrderCostWithMarkup)
{
    EXPECT_DOUBLE_EQ(14400.0, shop.calculateOrderCost(tableId, 1, 20.0));
    EXPECT_DOUBLE_EQ(24000.0, shop.calculateOrderCost(tableId, 2, 0.0));
    EXPECT_THROW(shop.calculateOrderCost(tableId, 0, 20.0), std::invalid_argument);
    EXPECT_THROW(shop.calculateOrderCost(tableId, 1, -1), std::invalid_argument);
}

TEST_F(ShopTests, CustomOrdersBetweenDates)
{
    EXPECT_DOUBLE_EQ(28800.0,
                     shop.makeCustomOrder(projectBuyerId, tableId, 2, "2026-10-10"));
    EXPECT_DOUBLE_EQ(4200.0,
                     shop.makeCustomOrder(projectBuyerId, chairId, 1, "2026-10-12"));
    shop.makeCustomOrder(projectBuyerId, tableId, 1, "2026-11-01");

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
    EXPECT_THROW(shop.makeSale(buyerId, tableId, 50, "2026-10-05"),
                 std::runtime_error);
    EXPECT_THROW(shop.makeSale(buyerId, wardrobeId, 1, "2026-10-05"),
                 std::runtime_error);
    EXPECT_EQ(10, shop.getProduct(tableId).getQuantity());
    EXPECT_TRUE(shop.getAllSales().empty());
}

TEST_F(ShopTests, InvalidDateAndDuplicateIds)
{
    EXPECT_THROW(shop.makeSale(buyerId, tableId, 1, "2026-02-29"),
                 std::invalid_argument);
    EXPECT_THROW(shop.makeSale(buyerId, tableId, 1, "05.10.2026"),
                 std::invalid_argument);
    EXPECT_THROW(shop.addProduct(Product(tableId, "Иной", "Фабрика", 1, 1)),
                 std::invalid_argument);
    EXPECT_THROW(shop.addRetailClient(
                     RetailClient(buyerId, "Другой", "+7 900 000-00-00")),
                 std::invalid_argument);
    EXPECT_THROW(shop.getRetailClient(990), std::invalid_argument);
    EXPECT_THROW(shop.getDesignClient(991), std::invalid_argument);
    EXPECT_THROW(shop.getProduct(992), std::invalid_argument);
}
