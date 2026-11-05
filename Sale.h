#pragma once
#include "Client.h"
#include "Product.h"
#include <string>

/**
 * @brief Запись о продаже
 */
class Sale
{
private:
    /**
     * @brief Уникальный ID продажи
     */
    int id;
    /**
     * @brief Указатель на клиента (защита от срезки)
     */
    const Client* client;
    /**
     * @brief Указатель на товар (защита от срезки)
     */
    const Product* product;
    /**
     * @brief Количество проданного товара
     */
    int quantity;
    /**
     * @brief Дата продажи
     */
    std::string date;
    /**
     * @brief Итоговая сумма продажи
     */
    double total;

public:
    /**
     * @brief Создать запись о продаже
     * @param id Положительный ID продажи
     * @param client Ссылка на существующего клиента
     * @param product Ссылка на существующий товар
     * @param quantity Положительное количество
     * @param date Непустая дата в формате ГГГГ-ММ-ДД
     * @param total Неотрицательная итоговая сумма
     * @throws std::invalid_argument при неверных данных
     */
    Sale(const int id, const Client& client, const Product& product,
         const int quantity, const std::string& date, const double total);

    /**
     * @brief Получить клиента продажи
     * @return Константная ссылка на клиента
     */
    const Client& getClient() const;
    
    /**
     * @brief Получить товар продажи
     * @return Константная ссылка на товар
     */
    const Product& getProduct() const;
    
    /**
     * @brief Получить ID продажи
     * @return Идентификатор
     */
    int getId() const;
    
    /**
     * @brief Получить ID клиента
     * @return Идентификатор клиента
     */
    int getClientId() const;
    
    /**
     * @brief Получить ID товара
     * @return Идентификатор товара
     */
    int getProductId() const;
    
    /**
     * @brief Получить количество проданного товара
     * @return Количество штук
     */
    int getQuantity() const;
    
    /**
     * @brief Получить дату продажи
     * @return Константная ссылка на строку с датой
     */
    const std::string& getDate() const;
    
    /**
     * @brief Получить итоговую сумму
     * @return Сумма с учётом скидки
     */
    double getTotal() const;
    
    /**
     * @brief Получить строку с описанием продажи
     * @return Полное описание
     */
    std::string getInfo() const;
};
