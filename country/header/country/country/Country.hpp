#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#include <string>
#include <memory>
#include <unordered_map>
#include <Nlohmann/json.hpp>
#include "../citizen/CitizenManager.hpp"
#include "manager/CountryManager.hpp"
#include <Util/types.hpp>
#include <utility>
#include <optional>
namespace tes {
class Country {
public:
    Country() = delete;

    explicit Country(std::string name_, CountryManager::country_id);

    explicit Country(nlohmann::json);

    std::shared_ptr<CitizenManager> getCitizenManager() { return citizen; };

private:
    std::string name;
    std::shared_ptr<CitizenManager> citizen;
    std::optional<CountryManager::country_id> id;
};
}

#endif  // TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
