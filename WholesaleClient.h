#pragma once
#include "Client.h"

/**
 * @brief Оптовый клиент
 */
class WholesaleClient : public Client
{
private:
    /**
     * @brief Контактное лицо
     */
    std::string contactPerson;
public:
    /**
     * @brief Создать оптового клиента с явным ID
     * @param id Положительный уникальный идентификатор
     * @param name Непустое название
     * @param discount Скидка (0-100)
     * @param contactPerson Непустое имя контакта
     * @throws std::invalid_argument при неверных данных
     */
    WholesaleClient(const int id, const std::string& name, const double discount, const std::string& contactPerson);
    
    /**
     * @brief Создать оптового клиента с автоматическим ID
     * @param name Непустое название
     * @param discount Скидка (0-100)
     * @param contactPerson Непустое имя контакта
     */
    WholesaleClient(const std::string& name, const double discount, const std::string& contactPerson);
    
    /**
     * @brief Получить контактное лицо
     * @return Константная ссылка на имя
     */
    const std::string& getContactPerson() const;
    
    /**
     * @brief Получить информацию об оптовике
     * @return Строка с названием, скидкой и контактом
     */
    std::string getInfo() const override;
};
