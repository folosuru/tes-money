class CountryEconomy;
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#include <misc/money_add_trigger/MoneyAddTriggerManager.hpp>
#include <currency/Currency.hpp>
#include <unordered_map>
#include <memory>
#include <optional>
#include <DataManager.hpp>
#include <types/MoneyTypes.hpp>
namespace tes {
class Country;
class DataManager;
class CountryEconomy {
public:
    std::shared_ptr<Currency> getCurrency();

    CountryEconomy() = default;

    /**
     * データベースから読み取り。
     */
    static std::shared_ptr<CountryEconomy> load(int country_id,
                                                const std::shared_ptr<MoneyAddTriggerManager>& trigger_mng,
                                                const std::shared_ptr<CurrencyManager>& currency_mng);
    void setCurrency(const std::shared_ptr<Currency>&);

    Types::money_value_t getValue(const std::string& trigger_name);

    void runTrigger(std::string_view trigger_name, const std::string& player_name) noexcept;

    bool existsTrigger(const std::string& name) const noexcept;

    void updateTrigger(const std::string& trigger_name, int value);

    void removeTrigger(const std::string& trigger_name);

private:
    CountryEconomy(std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> trigger,
                   std::weak_ptr<Currency> currency,
                   std::weak_ptr<MoneyAddTriggerManager>);
    // money_value_type
    std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> money_add_trigger;
    std::weak_ptr<MoneyAddTriggerManager> trigger_mng;
    std::weak_ptr<Currency> currency;
    std::weak_ptr<Country> country;
};
}
#endif //TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
