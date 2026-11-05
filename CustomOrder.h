#pragma once

#include "Product.h"

/**
 * @brief Заказ по индивидуальному проекту (с наценкой)
 */
class CustomOrder : public Product
{
private:
    /**
     * @brief Базовая цена до наценки
     */
    double basePrice;
    /**
     * @brief Процент наценки
     */
    double markupPercent;

public:
    /**
     * @brief Создать индивидуальный заказ с явным ID
     * @param id Положительный уникальный идентификатор
     * @param name Непустое название
     * @param category Непустая категория
     * @param basePrice Неотрицательная базовая цена
     * @param markupPercent Неотрицательный процент наценки
     * @throws std::invalid_argument при неверных данных
     */
    CustomOrder(const int id, const std::string& name, const std::string& category,
                const double basePrice, const double markupPercent);
    /**
     * @brief Создать индивидуальный заказ с автоматическим ID
     * @param name Непустое название
     * @param category Непустая категория
     * @param basePrice Неотрицательная базовая цена
     * @param markupPercent Неотрицательный процент наценки
     * @throws std::invalid_argument при неверных данных
     */
    CustomOrder(const std::string& name, const std::string& category,
                const double basePrice, const double markupPercent);

    /**
     * @brief Получить базовую цену до наценки
     * @return Базовая цена
     */
    double getBasePrice() const;
    /**
     * @brief Получить процент наценки
     * @return Процент наценки
     */
    double getMarkupPercent() const;
    /**
     * @brief Получить информацию о товаре
     * @return Строка с описанием
     */
    std::string getInfo() const override;
    /**
     * @brief Проверить, изготавливается ли товар под заказ
     * @return Всегда true
     */
    bool isMadeToOrder() const override;
};
