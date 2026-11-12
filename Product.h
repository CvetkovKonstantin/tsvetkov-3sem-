#pragma once

#include <string>
#include <vector>

/**
 * @brief Образец мебели в ассортименте магазина
 */
class Product
{
private:
    /**
     * @brief Уникальный идентификатор образца
     */
    int id;
    /**
     * @brief Следующий свободный идентификатор
     */
    static int nextId;
    /**
     * @brief Идентификаторы уже существующих образцов
     */
    static std::vector<int> activeIds;
    /**
     * @brief Наименование образца мебели
     */
    std::string name;
    /**
     * @brief Наименование фабрики-изготовителя
     */
    std::string manufacturer;
    /**
     * @brief Цена одного изделия
     */
    double price;
    /**
     * @brief Количество изделий в наличии
     */
    int quantity;

public:
    /**
     * @brief Создать образец мебели
     * @param id Положительный уникальный идентификатор образца
     * @param name Непустое наименование образца
     * @param manufacturer Непустое наименование фабрики
     * @param price Положительная цена изделия
     * @param quantity Неотрицательный остаток на складе магазина
     */
    Product(const int id, const std::string& name,
            const std::string& manufacturer, const double price,
            const int quantity);
    /**
     * @brief Создать образец мебели с автоматическим идентификатором
     * @param name Непустое наименование образца
     * @param manufacturer Непустое наименование фабрики
     * @param price Положительная цена изделия
     * @param quantity Неотрицательный остаток на складе магазина
     */
    Product(const std::string& name, const std::string& manufacturer,
            const double price, const int quantity);
    /**
     * @brief Скопировать образец с сохранением идентификатора
     * @param other Исходный образец
     */
    Product(const Product& other);
    /**
     * @brief Присвоить данные образца с сохранением идентификатора
     * @param other Исходный образец
     * @return Ссылка на текущий образец
     */
    Product& operator=(const Product& other);
    /**
     * @brief Уничтожить экземпляр образца
     */
    ~Product();

    /**
     * @brief Получить идентификатор образца
     * @return Идентификатор образца
     */
    int getId() const;
    /**
     * @brief Получить наименование образца
     * @return Ссылка на наименование
     */
    const std::string& getName() const;
    /**
     * @brief Получить наименование фабрики
     * @return Ссылка на наименование фабрики
     */
    const std::string& getManufacturer() const;
    /**
     * @brief Получить цену изделия
     * @return Цена одного изделия
     */
    double getPrice() const;
    /**
     * @brief Получить остаток изделий
     * @return Количество изделий в наличии
     */
    int getQuantity() const;
    /**
     * @brief Получить строку с информацией об образце
     * @return Наименование, фабрика, цена и остаток
     */
    std::string getInfo() const;

    /**
     * @brief Увеличить остаток изделий
     * @param amount Положительное количество поступивших изделий
     */
    void addQuantity(const int amount);
    /**
     * @brief Уменьшить остаток изделий
     * @param amount Положительное количество проданных изделий
     */
    void removeQuantity(const int amount);
};
