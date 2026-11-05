#pragma once
#include "Client.h"

/**
 * @brief Магазин-партнер
 */
class Store : public Client
{
private:
    /**
     * @brief Адрес магазина
     */
    std::string address;
public:
    /**
     * @brief Создать магазин с явным ID
     * @param id Положительный уникальный идентификатор
     * @param name Непустое название
     * @param discount Скидка (0-100)
     * @param address Непустой адрес
     * @throws std::invalid_argument при неверных данных
     */
    Store(const int id, const std::string& name, const double discount, const std::string& address);
    
    /**
     * @brief Создать магазин с автоматическим ID
     * @param name Непустое название
     * @param discount Скидка (0-100)
     * @param address Непустой адрес
     */
    Store(const std::string& name, const double discount, const std::string& address);
    
    /**
     * @brief Получить адрес магазина
     * @return Константная ссылка на адрес
     */
    const std::string& getAddress() const;
    
    /**
     * @brief Получить информацию о магазине
     * @return Строка с названием, скидкой и адресом
     */
    std::string getInfo() const override;
};
