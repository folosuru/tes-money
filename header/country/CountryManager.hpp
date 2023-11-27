#pragma once
#ifndef TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
#define TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
#include <memory>
#include <string>
#include <unordered_map>
#include <country/Country.hpp>
#include <util/dll_declspec.hpp>
namespace tes {
class TES_DLL CountryManager {
public:
    typedef int country_id;

    CountryManager() = default;

    /**
     * Construct CountryManager with load data...
     * @return self
     */
    static std::shared_ptr<CountryManager> build(const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                                                 const std::shared_ptr<CurrencyManager>& currency);

    [[nodiscard]]
    std::shared_ptr<Country> getCountry(country_id id) const;

    void addCountry(const std::shared_ptr<Country>&);

    [[nodiscard]]
    const std::unordered_map<country_id, std::shared_ptr<Country>>& getAll() const noexcept;

    country_id genNextCountryId() const noexcept;

    void saveAll();

private:
    std::unordered_map<country_id, std::shared_ptr<Country>> country;
    inline static std::shared_ptr<CountryManager> instance = nullptr;
    inline static const std::string data_save_path = "plugins/tes/country/country";
};
}
#endif  // TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
