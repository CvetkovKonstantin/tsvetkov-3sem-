#pragma once

#include <string>

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
     * @brief Название клиента
     */
    std::string name;

public:
    /**
     * @brief Создать клиента
     * @param id Положительный идентификатор клиента
     * @param name Непустое название клиента
     */
    Client(const int id, const std::string& name);
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
