#pragma once
#ifndef TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
#define TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
#include <memory>
#include "../country/Country.hpp"

namespace tes {
class CountryManager {
public:
    typedef int country_id;

    std::shared_ptr<Country> get(country_id id);

    void addCountry(std::shared_ptr<Country>);

    void loadAll();
    void saveAll();

private:
    std::unordered_map<country_id,std::shared_ptr<Country>> country;

    inline const static std::string data_save_path = "plugins/tes/country/country";
};
}
#endif //TES_MONEY_COUNTRY_HEADER_MANAGER_COUNTRYMANAGER_HPP_
