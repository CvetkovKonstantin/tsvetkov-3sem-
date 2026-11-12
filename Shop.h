#pragma once

#include "CustomOrder.h"
#include "DesignClient.h"
#include "Product.h"
#include "RetailClient.h"
#include "Sale.h"

#include <string>
#include <vector>

/**
 * @brief Мебельный магазин: ассортимент, продажи готовой мебели и заказы по проекту
 */
class Shop
{
private:
    /**
     * @brief Наименование магазина
     */
    std::string name;
    /**
     * @brief Ассортимент предлагаемой мебели
     */
    std::vector<Product> products;
    /**
     * @brief Розничные покупатели магазина
     */
    std::vector<RetailClient> retailClients;
    /**
     * @brief Клиенты, заказывающие мебель по индивидуальному проекту
     */
    std::vector<DesignClient> designClients;
    /**
     * @brief История продаж готовой мебели
     */
    std::vector<Sale> sales;
    /**
     * @brief История заказов по индивидуальному проекту
     */
    std::vector<CustomOrder> orders;

    /**
     * @brief Найти образец мебели для изменения его остатка
     * @param productId Идентификатор образца
     * @return Ссылка на образец
     */
    Product& findProduct(const int productId);
    /**
     * @brief Записать продажу готовой мебели и уменьшить остаток
     * @param client Покупатель готовой мебели
     * @param productId Идентификатор образца
     * @param quantity Положительное число продаваемых изделий
     * @param date Дата продажи в формате ГГГГ-ММ-ДД
     * @return Запись добавленной продажи
     */
    Sale addSale(const Client& client, const int productId,
                const int quantity, const std::string& date);

public:
    /**
     * @brief Создать мебельный магазин
     * @param name Непустое наименование магазина
     */
    explicit Shop(const std::string& name);

    /**
     * @brief Получить наименование магазина
     * @return Ссылка на наименование
     */
    const std::string& getName() const;

    /**
     * @brief Добавить образец мебели в ассортимент
     * @param product Образец мебели
     * @return Идентификатор добавленного образца
     */
    int addProduct(const Product& product);
    /**
     * @brief Зарегистрировать розничного покупателя или найти существующего
     * @param client Розничный покупатель
     * @return Идентификатор зарегистрированного покупателя
     */
    int addRetailClient(const RetailClient& client);
    /**
     * @brief Зарегистрировать клиента проекта или найти существующего
     * @param client Клиент индивидуального проекта
     * @return Идентификатор зарегистрированного клиента
     */
    int addDesignClient(const DesignClient& client);

    /**
     * @brief Найти образец мебели по идентификатору
     * @param productId Идентификатор образца
     * @return Ссылка на найденный образец
     */
    const Product& getProduct(const int productId) const;
    /**
     * @brief Найти розничного покупателя по идентификатору
     * @param clientId Идентификатор покупателя
     * @return Ссылка на найденного покупателя
     */
    const RetailClient& getRetailClient(const int clientId) const;
    /**
     * @brief Найти клиента индивидуального проекта по идентификатору
     * @param clientId Идентификатор клиента
     * @return Ссылка на найденного клиента
     */
    const DesignClient& getDesignClient(const int clientId) const;
    /**
     * @brief Получить историю всех продаж готовой мебели
     * @return Ссылка на список продаж
     */
    const std::vector<Sale>& getAllSales() const;
    /**
     * @brief Получить историю всех заказов по индивидуальному проекту
     * @return Ссылка на список заказов
     */
    const std::vector<CustomOrder>& getAllOrders() const;

    /**
     * @brief Принять партию изделий в магазин
     * @param productId Идентификатор образца
     * @param quantity Положительное количество поступивших изделий
     */
    void receiveProduct(const int productId, const int quantity);

    /**
     * @brief Оформить продажу готовой мебели розничному покупателю
     * @param clientId Идентификатор розничного покупателя
     * @param productId Идентификатор образца
     * @param quantity Положительное число продаваемых изделий
     * @param date Дата продажи в формате ГГГГ-ММ-ДД
     * @return Идентификатор созданной продажи
     */
    int makeSale(const int clientId, const int productId,
                 const int quantity, const std::string& date);

    /**
     * @brief Оформить заказ клиента по индивидуальному проекту
     * @param clientId Идентификатор клиента проекта
     * @param productId Идентификатор образца-основы
     * @param quantity Положительное число изделий в заказе
     * @param date Дата заказа в формате ГГГГ-ММ-ДД
     * @return Стоимость заказа с надбавкой клиента
     */
    double makeCustomOrder(const int clientId, const int productId,
                           const int quantity, const std::string& date);

    /**
     * @brief Получить ассортимент предлагаемой мебели с ценами
     * @return Список образцов с положительным остатком
     */
    std::vector<Product> getAvailableProducts() const;
    /**
     * @brief Получить количество проданных изделий выбранного образца
     * @param productId Идентификатор образца
     * @param startDate Начальная дата периода в формате ГГГГ-ММ-ДД
     * @param endDate Конечная дата периода в формате ГГГГ-ММ-ДД
     * @return Количество проданных изделий за период
     */
    int getSoldQuantity(const int productId, const std::string& startDate,
                        const std::string& endDate) const;
    /**
     * @brief Получить список продаж за отчётный период
     * @param startDate Начальная дата периода в формате ГГГГ-ММ-ДД
     * @param endDate Конечная дата периода в формате ГГГГ-ММ-ДД
     * @return Список продаж за период включительно
     */
    std::vector<Sale> getSalesBetween(const std::string& startDate,
                                      const std::string& endDate) const;
    /**
     * @brief Получить список заказов по проекту за отчётный период
     * @param startDate Начальная дата периода в формате ГГГГ-ММ-ДД
     * @param endDate Конечная дата периода в формате ГГГГ-ММ-ДД
     * @return Список заказов за период включительно
     */
    std::vector<CustomOrder> getOrdersBetween(const std::string& startDate,
                                              const std::string& endDate) const;
    /**
     * @brief Рассчитать стоимость заказа по индивидуальному проекту
     * @param productId Идентификатор образца-основы
     * @param quantity Положительное число изделий в заказе
     * @param markupPercent Неотрицательная надбавка в процентах
     * @return Стоимость заказа с надбавкой
     */
    double calculateOrderCost(const int productId, const int quantity,
                              const double markupPercent) const;
};
