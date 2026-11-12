#pragma once

#include "Client.h"
#include "Sale.h"

#include <string>

/**
 * @brief Заказ мебели по индивидуальному проекту с надбавкой к стоимости
 */
class CustomOrder : public Sale
{
private:
    /**
     * @brief Надбавка за индивидуальный проект в процентах
     */
    double markupPercent;

public:
    /**
     * @brief Создать заказ по индивидуальному проекту
     * @param id Положительный уникальный идентификатор заказа
     * @param client Клиент, оформивший заказ
     * @param product Образец-основа заказа
     * @param quantity Положительное число изделий в заказе
     * @param date Непустая строка даты заказа
     * @param total Неотрицательная стоимость заказа
     * @param markupPercent Неотрицательная надбавка в процентах
     */
    CustomOrder(const int id, const Client& client, const Product& product,
                const int quantity, const std::string& date,
                const double total, const double markupPercent);
    /**
     * @brief Создать заказ по проекту с автоматическим идентификатором
     * @param client Клиент, оформивший заказ
     * @param product Образец-основа заказа
     * @param quantity Положительное число изделий в заказе
     * @param date Непустая строка даты заказа
     * @param total Неотрицательная стоимость заказа
     * @param markupPercent Неотрицательная надбавка в процентах
     */
    CustomOrder(const Client& client, const Product& product,
                const int quantity, const std::string& date,
                const double total, const double markupPercent);
    /**
     * @brief Уничтожить экземпляр заказа (используется деструктор базового класса)
     */
    ~CustomOrder() = default;

    /**
     * @brief Получить надбавку за индивидуальный проект
     * @return Размер надбавки в процентах
     */
    double getMarkupPercent() const;
    /**
     * @brief Получить описание заказа с указанием надбавки
     * @return Строка с номером, датой, изделием, количеством, надбавкой и суммой
     */
    std::string getInfo() const override;
};
