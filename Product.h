#pragma once

#include <string>
#include <vector>

/**
 * @brief Базовый класс товара (мебели)
 */
class Product
{
private:
    /**
     * @brief Уникальный идентификатор товара
     */
    int id;
    /**
     * @brief Счётчик для автоматической генерации идентификаторов
     */
    static int nextId;
    /**
     * @brief Список активных идентификаторов для проверки уникальности
     */
    static std::vector<int> activeIds;
    /**
     * @brief Наименование товара
     */
    std::string name;
    /**
     * @brief Категория товара
     */
    std::string category;
    /**
     * @brief Цена товара
     */
    double price;
    /**
     * @brief Остаток на складе
     */
    int quantity;

public:
    /**
     * @brief Создать товар с явным ID
     * @param id Положительный уникальный идентификатор
     * @param name Непустое название
     * @param category Непустая категория
     * @param price Неотрицательная цена
     * @param quantity Неотрицательный остаток
     * @throws std::invalid_argument при неверных данных или дубликате ID
     */
    Product(const int id, const std::string& name, const std::string& category,
            const double price, const int quantity);
    /**
     * @brief Создать товар с автоматическим ID
     * @param name Непустое название
     * @param category Непустая категория
     * @param price Неотрицательная цена
     * @param quantity Неотрицательный остаток
     * @throws std::invalid_argument при неверных данных
     */
    Product(const std::string& name, const std::string& category,
            const double price, const int quantity);
    /**
     * @brief Скопировать товар с сохранением ID
     * @param other Исходный товар
     */
    Product(const Product& other);
    /**
     * @brief Присвоить данные товара с сохранением ID
     * @param other Исходный товар
     * @return Ссылка на текущий товар
     */
    Product& operator=(const Product& other);
    /**
     * @brief Уничтожить экземпляр товара
     */
    virtual ~Product();

    /**
     * @brief Получить идентификатор товара
     * @return Идентификатор товара
     */
    int getId() const;
    /**
     * @brief Получить наименование товара
     * @return Ссылка на наименование товара
     */
    const std::string& getName() const;
    /**
     * @brief Получить категорию товара
     * @return Ссылка на категорию товара
     */
    const std::string& getCategory() const;
    /**
     * @brief Получить цену одной штуки товара
     * @return Цена товара
     */
    double getPrice() const;
    /**
     * @brief Получить текущий остаток товара
     * @return Количество штук на складе
     */
    int getQuantity() const;
    /**
     * @brief Получить строку с информацией о товаре
     * @return Наименование, категория, цена и остаток
     */
    virtual std::string getInfo() const;
    /**
     * @brief Проверить, изготавливается ли товар под заказ
     * @return true для индивидуальных заказов, false для складской мебели
     */
    virtual bool isMadeToOrder() const;

    /**
     * @brief Увеличить остаток товара
     * @param amount Количество поступивших штук (должно быть > 0)
     * @throws std::invalid_argument если количество <= 0
     */
    void addQuantity(const int amount);
    /**
     * @brief Уменьшить остаток товара
     * @param amount Количество отгруженных штук (должно быть > 0)
     * @throws std::invalid_argument если количество <= 0
     * @throws std::runtime_error если недостаточно товара
     */
    void removeQuantity(const int amount);
};
