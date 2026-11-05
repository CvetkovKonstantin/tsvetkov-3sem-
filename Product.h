#pragma once
#include <string>
#include <vector>

/**
 * @brief Базовый класс товара (мебели)
 */
class Product
{
protected:
    /**
     * @brief Уникальный идентификатор товара
     */
    int id;
    
    /**
     * @brief Статический счетчик для автогенерации ID
     */
    static int nextId;
    
    /**
     * @brief Список активных ID для проверки уникальности
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
     */
    Product(const std::string& name, const std::string& category,
            const double price, const int quantity);
            
    /**
     * @brief Конструктор копирования
     * @param other Копируемый товар
     */
    Product(const Product& other);
    
    /**
     * @brief Оператор копирующего присваивания
     * @param other Присваиваемый товар
     * @return Ссылка на текущий объект
     */
    Product& operator=(const Product& other);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Product();

    /**
     * @brief Получить идентификатор товара
     * @return Уникальный ID
     */
    int getId() const;
    
    /**
     * @brief Получить наименование товара
     * @return Константная ссылка на строку
     */
    const std::string& getName() const;
    
    /**
     * @brief Получить категорию товара
     * @return Константная ссылка на строку
     */
    const std::string& getCategory() const;
    
    /**
     * @brief Получить цену товара
     * @return Цена за штуку
     */
    double getPrice() const;
    
    /**
     * @brief Получить текущий остаток
     * @return Количество штук
     */
    int getQuantity() const;
    
    /**
     * @brief Получить информацию о товаре
     * @return Строка с описанием
     */
    virtual std::string getInfo() const;

    /**
     * @brief Увеличить остаток
     * @param amount Количество (должно быть > 0)
     * @throws std::invalid_argument если количество <= 0
     */
    void addQuantity(const int amount);
    
    /**
     * @brief Уменьшить остаток
     * @param amount Количество (должно быть > 0)
     * @throws std::invalid_argument если количество <= 0
     * @throws std::runtime_error если недостаточно товара
     */
    void removeQuantity(const int amount);
};
