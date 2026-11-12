#pragma once

#include "Client.h"
#include "Product.h"

#include <string>
#include <vector>

/**
 * @brief Запись о продаже готового изделия из ассортимента магазина
 */
class Sale
{
private:
    /**
     * @brief Уникальный идентификатор продажи
     */
    int id;
    /**
     * @brief Следующий свободный идентификатор продажи
     */
    static int nextId;
    /**
     * @brief Идентификаторы уже сохранённых записей
     */
    static std::vector<int> activeIds;
    /**
     * @brief Базовые данные клиента, совершившего покупку
     */
    Client client;
    /**
     * @brief Проданный образец мебели
     */
    Product product;
    /**
     * @brief Количество проданных изделий
     */
    int quantity;
    /**
     * @brief Дата продажи
     */
    std::string date;
    /**
     * @brief Итоговая сумма продажи
     */
    double total;

public:
    /**
     * @brief Создать запись о продаже
     * @param id Положительный уникальный идентификатор продажи
     * @param client Клиент, совершивший покупку
     * @param product Проданный образец мебели
     * @param quantity Положительное число проданных изделий
     * @param date Непустая строка даты продажи
     * @param total Неотрицательная сумма продажи
     */
    Sale(const int id, const Client& client, const Product& product,
         const int quantity, const std::string& date, const double total);
    /**
     * @brief Создать запись о продаже с автоматическим идентификатором
     * @param client Клиент, совершивший покупку
     * @param product Проданный образец мебели
     * @param quantity Положительное число проданных изделий
     * @param date Непустая строка даты продажи
     * @param total Неотрицательная сумма продажи
     */
    Sale(const Client& client, const Product& product, const int quantity,
         const std::string& date, const double total);
    /**
     * @brief Уничтожить экземпляр продажи (используется деструктор по умолчанию)
     */
    virtual ~Sale() = default;

    /**
     * @brief Получить идентификатор продажи
     * @return Идентификатор продажи
     */
    int getId() const;
    /**
     * @brief Получить данные клиента продажи
     * @return Ссылка на клиента
     */
    const Client& getClient() const;
    /**
     * @brief Получить проданный образец мебели
     * @return Ссылка на образец
     */
    const Product& getProduct() const;
    /**
     * @brief Получить идентификатор клиента
     * @return Идентификатор клиента
     */
    int getClientId() const;
    /**
     * @brief Получить идентификатор образца мебели
     * @return Идентификатор образца
     */
    int getProductId() const;
    /**
     * @brief Получить количество проданных изделий
     * @return Количество изделий в штуках
     */
    int getQuantity() const;
    /**
     * @brief Получить дату продажи
     * @return Ссылка на строку даты
     */
    const std::string& getDate() const;
    /**
     * @brief Получить итоговую сумму продажи
     * @return Сумма продажи
     */
    double getTotal() const;
    /**
     * @brief Получить краткое описание продажи
     * @return Строка с номером, датой, изделием, количеством и суммой
     */
    virtual std::string getInfo() const;
};
