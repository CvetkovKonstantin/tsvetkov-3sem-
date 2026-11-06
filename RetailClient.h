#pragma once

#include "Client.h"

#include <string>

/**
 * @brief Розничный покупатель, приобретающий готовую мебель из ассортимента
 */
class RetailClient : public Client
{
private:
    /**
     * @brief Номер телефона покупателя
     */
    std::string phone;

public:
    /**
     * @brief Создать розничного покупателя
     * @param id Положительный идентификатор покупателя
     * @param name Непустое название покупателя
     * @param phone Непустой номер телефона
     */
    RetailClient(const int id, const std::string& name,
                 const std::string& phone);

    /**
     * @brief Получить номер телефона покупателя
     * @return Ссылка на номер телефона
     */
    const std::string& getPhone() const;
    /**
     * @brief Получить информацию о розничном покупателе
     * @return Название и номер телефона
     */
    std::string getInfo() const override;
};
