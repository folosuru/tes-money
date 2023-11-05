#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
#include "MoneyAddTrigger.hpp"
#include <unordered_map>
#include <memory>
namespace tes {
class CountryEconomy {
public:

    const std::shared_ptr<Currency>& getCurrency();
    void setCurrency(std::shared_ptr<Currency>);

    void runTrigger(std::string trigger_name, std::string player_name) noexcept;

private:
    std::unordered_map<std::string_view, int> money_add_trigger;
    std::shared_ptr<Currency> currency = nullptr;
};
}
#endif //TES_COUNTRY_HEADER_COUNTRY_COUNTRY_ECONOMY_COUNTRYECONOMY_HPP_
