#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#include <string>
#include <unordered_map>
#include "../citizen/CitizenManager.hpp"
#include <Util/types.hpp>
namespace tes {
class Country {
public:
    Country() = delete;

    Country(std::string);

    std::shared_ptr<CitizenManager> getCitizenManager();

private:
    std::string name;

    std::shared_ptr<CitizenManager> citizen;
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
