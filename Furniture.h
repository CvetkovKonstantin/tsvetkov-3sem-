#pragma once

#include "Product.h"

/**
 * @brief Готовая мебель (продается со склада)
 */
class Furniture : public Product
{
public:
    /**
     * @brief Создать готовую мебель с явным ID
     * @param id Положительный уникальный идентификатор
     * @param name Непустое название
     * @param category Непустая категория
     * @param price Неотрицательная цена
     * @param quantity Неотрицательный остаток
     */
    Furniture(const int id, const std::string& name, const std::string& category,
              const double price, const int quantity);
    /**
     * @brief Создать готовую мебель с автоматическим ID
     * @param name Непустое название
     * @param category Непустая категория
     * @param price Неотрицательная цена
     * @param quantity Неотрицательный остаток
     */
    Furniture(const std::string& name, const std::string& category,
              const double price, const int quantity);

    /**
     * @brief Получить информацию о товаре
     * @return Строка с описанием
     */
    std::string getInfo() const override;
};
