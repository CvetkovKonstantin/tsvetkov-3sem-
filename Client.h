#pragma once

#include <string>
#include <vector>

/**
 * @brief Базовый класс клиента мебельного магазина
 */
class Client
{
private:
    /**
     * @brief Уникальный идентификатор клиента
     */
    int id;
    /**
     * @brief Следующий свободный идентификатор
     */
    static int nextId;
    /**
     * @brief Идентификаторы уже существующих клиентов
     */
    static std::vector<int> activeIds;
    /**
     * @brief Название клиента
     */
    std::string name;

public:
    /**
     * @brief Создать клиента
     * @param id Положительный уникальный идентификатор клиента
     * @param name Непустое название клиента
     */
    Client(const int id, const std::string& name);
    /**
     * @brief Создать клиента с автоматическим идентификатором
     * @param name Непустое название клиента
     */
    Client(const std::string& name);
    /**
     * @brief Скопировать клиента с сохранением идентификатора
     * @param other Исходный клиент
     */
    Client(const Client& other);
    /**
     * @brief Присвоить данные клиента с сохранением идентификатора
     * @param other Исходный клиент
     * @return Ссылка на текущего клиента
     */
    Client& operator=(const Client& other);
    /**
     * @brief Уничтожить экземпляр клиента
     */
    virtual ~Client();

    /**
     * @brief Получить идентификатор клиента
     * @return Идентификатор клиента
     */
    int getId() const;
    /**
     * @brief Получить название клиента
     * @return Ссылка на название клиента
     */
    const std::string& getName() const;
    /**
     * @brief Получить краткую информацию о клиенте
     * @return Название клиента
     */
    virtual std::string getInfo() const;
};
