#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#include <string>
#include <memory>
#include <unordered_map>
#include <country/citizen/CountryCitizen.hpp>
#include <country/economy/CountryEconomy.hpp>
#include <types/GeneralTypes.hpp>
#include <utility>
#include <optional>
#include <util/dll_declspec.hpp>
#include <Nlohmann/json.hpp>
#include <currency/Currency.hpp>

namespace tes {
class TES_DLL Country {
public:
    typedef int country_id;

    const country_id id;

    const std::shared_ptr<CountryEconomy> economy;

    Country() = delete;

    ~Country() = default;

    explicit Country(std::string name_,
                     country_id id_);

    explicit Country(std::string name_,
                     country_id id_,
                     std::shared_ptr<CountryCitizen> citizen,
                     std::shared_ptr<CountryEconomy> economy);

    static std::shared_ptr<Country> load(const std::string& name,
                                         Country::country_id id_,
                                         const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                                         const std::shared_ptr<CurrencyManager>& currency);

    const std::string& getName();

    [[nodiscard]]
    const std::shared_ptr<CountryEconomy>& getEconomyManager() const noexcept;

    //countryもSQLで管理したい欲が出て来たよ
    explicit Country(nlohmann::json,
                     const std::shared_ptr<MoneyAddTriggerManager>&,
                     const std::shared_ptr<CurrencyManager>&);

    nlohmann::json get_json();

    std::shared_ptr<CountryCitizen> getCitizenManager() { return citizen; }

private:
    Country(std::string name,
            Country::country_id id_,
            const std::shared_ptr<MoneyAddTriggerManager>& trigger,
            const std::shared_ptr<CurrencyManager>& currency);

    std::string name;

    std::string description;

    std::shared_ptr<CountryCitizen> citizen;
};
}

#endif  // TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
