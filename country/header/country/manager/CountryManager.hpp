#pragma once
#ifndef TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
#define TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
#include <memory>
#include <unordered_map>
#include "../country/Country.hpp"
#include "../util/dll_declspec.hpp"
namespace tes {
class TES_COUNTRY_DLL CountryManager {
public:
    typedef int country_id;

    static std::shared_ptr<CountryManager> get();

    std::shared_ptr<Country> getCountry(country_id id);

    void addCountry(const std::shared_ptr<Country>&);
    std::shared_ptr<Country> addCountry(const std::string& name);

    void loadAll();
    void saveAll();

private:
    std::unordered_map<country_id, std::shared_ptr<Country>> country;
    inline static std::shared_ptr<CountryManager> instance = nullptr;
    inline const static std::string data_save_path = "plugins/tes/country/country";
};
}
#endif  // TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
