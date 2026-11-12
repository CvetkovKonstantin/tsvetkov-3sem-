#pragma once

#include "Client.h"

#include <string>

/**
 * @brief Клиент, заказывающий мебель по индивидуальному проекту
 */
class DesignClient : public Client
{
private:
    /**
     * @brief Адрес доставки заказа
     */
    std::string address;
    /**
     * @brief Надбавка за индивидуальный проект в процентах
     */
    double markupPercent;

public:
    /**
     * @brief Создать клиента индивидуального проекта
     * @param id Положительный уникальный идентификатор клиента
     * @param name Непустое название клиента
     * @param address Непустой адрес доставки
     * @param markupPercent Неотрицательная надбавка в процентах
     */
    DesignClient(const int id, const std::string& name,
                 const std::string& address, const double markupPercent);
    /**
     * @brief Создать клиента индивидуального проекта с автоматическим идентификатором
     * @param name Непустое название клиента
     * @param address Непустой адрес доставки
     * @param markupPercent Неотрицательная надбавка в процентах
     */
    DesignClient(const std::string& name, const std::string& address,
                 const double markupPercent);

    /**
     * @brief Получить адрес доставки
     * @return Ссылка на адрес доставки
     */
    const std::string& getAddress() const;
    /**
     * @brief Получить надбавку за индивидуальный проект
     * @return Размер надбавки в процентах
     */
    double getMarkupPercent() const;
    /**
     * @brief Получить информацию о клиенте индивидуального проекта
     * @return Название, адрес и надбавка
     */
    std::string getInfo() const override;
};
