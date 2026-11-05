#pragma once
#include <string>
#include <vector>

/**
 * @brief Базовый класс клиента
 */
class Client
{
private:
    /**
     * @brief Уникальный идентификатор клиента
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
     * @brief Название клиента
     */
    std::string name;
    
    /**
     * @brief Скидка клиента в процентах (0-100)
     */
    double discount;

public:
    /**
     * @brief Создать клиента с явным ID
     * @param id Положительный уникальный идентификатор
     * @param name Непустое название клиента
     * @param discount Скидка (0-100)
     * @throws std::invalid_argument при неверных данных или дубликате ID
     */
    Client(const int id, const std::string& name, const double discount);
    
    /**
     * @brief Создать клиента с автоматическим ID
     * @param name Непустое название клиента
     * @param discount Скидка (0-100)
     */
    Client(const std::string& name, const double discount);
    
    /**
     * @brief Конструктор копирования
     * @param other Копируемый клиент
     */
    Client(const Client& other);
    
    /**
     * @brief Оператор копирующего присваивания
     * @param other Присваиваемый клиент
     * @return Ссылка на текущий объект
     */
    Client& operator=(const Client& other);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Client();

    /**
     * @brief Получить идентификатор клиента
     * @return Уникальный ID
     */
    int getId() const;
    
    /**
     * @brief Получить название клиента
     * @return Константная ссылка на строку с названием
     */
    const std::string& getName() const;
    
    /**
     * @brief Получить скидку клиента
     * @return Размер скидки в процентах
     */
    double getDiscount() const;
    
    /**
     * @brief Получить общую информацию о клиенте
     * @return Строка с названием и размером скидки
     */
    virtual std::string getInfo() const;
};
