#pragma once
#include "Product.h"
#include "Sale.h"
#include "Store.h"
#include "WholesaleClient.h"
#include <string>
#include <vector>

/**
 * @brief Главный класс - Мебельный магазин
 */
class FurnitureShop
{
private:
    /**
     * @brief Название магазина
     */
    std::string name;
    /**
     * @brief Список товаров (указатели для полиморфизма)
     */
    std::vector<Product*> products;
    /**
     * @brief Список магазинов-партнеров
     */
    std::vector<Store> stores;
    /**
     * @brief Список оптовых клиентов
     */
    std::vector<WholesaleClient> wholesaleClients;
    /**
     * @brief История всех продаж
     */
    std::vector<Sale> sales;
    /**
     * @brief Счётчик для ID следующей продажи
     */
    int nextSaleId;

    /**
     * @brief Найти товар по ID для изменения остатка
     * @param productId ID товара
     * @return Ссылка на товар
     * @throws std::invalid_argument если товар не найден
     */
    Product& findProduct(const int productId);
    
    /**
     * @brief Внутренний метод оформления продажи
     * @param client Ссылка на клиента
     * @param productId ID товара
     * @param quantity Количество
     * @param discount Скидка
     * @param date Дата
     * @return ID продажи
     * @throws std::invalid_argument при неверной дате или количестве
     * @throws std::runtime_error если недостаточно товара
     */
    int addSale(const Client& client, const int productId, const int quantity, const double discount, const std::string& date);

public:
    /**
     * @brief Создать магазин
     * @param name Непустое название магазина
     * @throws std::invalid_argument если название пустое
     */
    explicit FurnitureShop(const std::string& name);
    
    /**
     * @brief Деструктор (очистка памяти товаров)
     */
    ~FurnitureShop();

    /**
     * @brief Получить название магазина
     * @return Константная ссылка на название
     */
    const std::string& getName() const;
    
    /**
     * @brief Добавить новый товар в магазин
     * @param product Указатель на товар
     * @throws std::invalid_argument если указатель пуст или ID уже существует
     */
    void addProduct(Product* product);
    
    /**
     * @brief Зарегистрировать магазин или найти существующий
     * @param store Объект магазина
     * @return ID зарегистрированного магазина
     * @throws std::invalid_argument если ID уже занят другим клиентом
     */
    int addStore(const Store& store);
    
    /**
     * @brief Зарегистрировать оптовика или найти существующего
     * @param client Объект оптовика
     * @return ID зарегистрированного оптовика
     * @throws std::invalid_argument если ID уже занят другим клиентом
     */
    int addWholesaleClient(const WholesaleClient& client);

    /**
     * @brief Получить информацию о товаре по ID
     * @param productId Идентификатор товара
     * @return Константная ссылка на товар
     * @throws std::invalid_argument если товар не найден
     */
    const Product& getProduct(const int productId) const;
    
    /**
     * @brief Получить магазин по ID
     * @param storeId ID магазина
     * @return Константная ссылка на магазин
     * @throws std::invalid_argument если не найден
     */
    const Store& getStore(const int storeId) const;
    
    /**
     * @brief Получить оптовика по ID
     * @param clientId ID оптовика
     * @return Константная ссылка на оптовика
     * @throws std::invalid_argument если не найден
     */
    const WholesaleClient& getWholesaleClient(const int clientId) const;
    
    /**
     * @brief Получить историю всех продаж
     * @return Константная ссылка на вектор продаж
     */
    const std::vector<Sale>& getAllSales() const;

    /**
     * @brief Принять новую партию товара на склад
     * @param productId ID товара
     * @param quantity Количество для добавления
     * @throws std::invalid_argument если товар не найден или количество <= 0
     */
    void receiveProduct(const int productId, const int quantity);
    
    /**
     * @brief Оформить заказ магазина
     * @param storeId ID магазина
     * @param productId ID товара
     * @param quantity Количество
     * @param date Дата в формате ГГГГ-ММ-ДД
     * @return ID созданной продажи
     */
    int makeStoreOrder(const int storeId, const int productId, const int quantity, const std::string& date);
    
    /**
     * @brief Оформить оптовую продажу
     * @param clientId ID оптовика
     * @param productId ID товара
     * @param quantity Количество
     * @param date Дата в формате ГГГГ-ММ-ДД
     * @return ID созданной продажи
     */
    int makeWholesaleSale(const int clientId, const int productId, const int quantity, const std::string& date);


    /**
     * @brief Получить ассортимент товаров в наличии
     * @return Вектор указателей на товары
     */
    std::vector<Product*> getAvailableProducts() const;
    
    /**
     * @brief Получить количество проданного товара по имени за период
     * @param productName Имя товара
     * @param startDate Начальная дата
     * @param endDate Конечная дата
     * @return Количество проданных штук
     * @throws std::invalid_argument если период неверный
     */
    int getSoldQuantityForPeriod(const std::string& productName, const std::string& startDate, const std::string& endDate) const;
    
    /**
     * @brief Получить список заказов за период
     * @param startDate Начальная дата
     * @param endDate Конечная дата
     * @return Вектор продаж
     * @throws std::invalid_argument если период неверный
     */
    std::vector<Sale> getOrdersForPeriod(const std::string& startDate, const std::string& endDate) const;
    
    /**
     * @brief Рассчитать стоимость индивидуального заказа
     * @param basePrice Базовая цена
     * @param markupPercent Процент наценки
     * @return Итоговая цена с наценкой
     * @throws std::invalid_argument если цена или наценка < 0
     */
    double calculateCustomOrderPrice(const double basePrice, const double markupPercent) const;

    /**
     * @brief Получить список клиентов со скидкой
     * @return Вектор строк с информацией о клиентах
     */
    std::vector<std::string> getClientsWithDiscount() const;
};
