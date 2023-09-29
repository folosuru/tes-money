#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#include <string>
#include <unordered_map>
#include "../citizen/CitizenManager.hpp"
#include <Util/types.hpp>
#include <utility>
namespace tes {
class Country {
public:
    Country() = delete;

    explicit Country(std::string name_) : name(std::move(name_)){};

    std::shared_ptr<CitizenManager> getCitizenManager() {return citizen;};

private:
    std::string name;

    std::shared_ptr<CitizenManager> citizen;
};
}
#endif  // TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
