class CountryEconomy;
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#include <misc/money_add_trigger/MoneyAddTriggerManager.hpp>
#include <currency/Currency.hpp>
#include <currency/CurrencyManager.hpp>
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

    explicit CountryEconomy(const Country&);

    /**
     * データベースから読み取り。
     */
    static std::shared_ptr<CountryEconomy> load(const Country&,
                                                const std::shared_ptr<MoneyAddTriggerManager>& trigger_mng,
                                                const std::shared_ptr<CurrencyManager>& currency_mng);
    void setCurrency(const std::shared_ptr<Currency>&);

    Types::money_value_t getValue(const MoneyAddTriggerKey& trigger_name);

    void runTrigger(const MoneyAddTriggerKey& trigger_name, std::shared_ptr<PlayerMoney> player) noexcept;

    [[nodiscard]]
    bool existsTrigger(const MoneyAddTriggerKey& name) const noexcept;

    void updateTrigger(const MoneyAddTriggerKey& trigger_name, int value);

    void removeTrigger(const MoneyAddTriggerKey& trigger_name);

private:
    CountryEconomy(std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> trigger,
                   std::weak_ptr<Currency> currency,
                   const Country&);
    explicit CountryEconomy(std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> trigger,
                            const Country&);
    // money_value_type
    std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> money_add_trigger;
    std::weak_ptr<Currency> currency;
    const Country& country;
};
}
#endif //TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
