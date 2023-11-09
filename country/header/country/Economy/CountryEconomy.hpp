#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#include "MoneyAddTriggerManager.hpp"
#include "money/currency/Currency.hpp"
#include <unordered_map>
#include <memory>
#include <optional>

namespace tes {
class CountryEconomy {
public:
    std::shared_ptr<Currency> getCurrency();

    CountryEconomy() = default;

    /**
     * データベースから読み取り。
     */
    static std::shared_ptr<CountryEconomy> load(int country_id);
    /**
     * JSONから読み込む？どっちがいいかな
     */
    static std::shared_ptr<CountryEconomy> load(nlohmann::json);

    void setCurrency(const std::shared_ptr<Currency>&);

    int getValue(const std::string& trigger_name);

    void runTrigger(const std::string& trigger_name, std::string player_name) noexcept;

    bool existsTrigger(const std::string& name) const noexcept;

private:
    CountryEconomy(std::unordered_map<std::string_view, int> trigger,
                   std::weak_ptr<Currency> currency);
    // money_value_type
    std::unordered_map<std::string_view, int> money_add_trigger;
    std::weak_ptr<Currency> currency;
};
}
#endif //TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
