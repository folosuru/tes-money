#pragma once
#ifndef TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#define TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
#include <string>
#include <memory>
#include <unordered_map>
#include "../citizen/CountryCitizen.hpp"
#include <types/GeneralTypes.hpp>
#include <utility>
#include <optional>
#include "../util/dll_declspec.hpp"
#include <Nlohmann/json.hpp>

namespace tes {
class TES_COUNTRY_DLL Country {
public:
    typedef int country_id;

    const country_id id;

    Country() = delete;

    ~Country() = default;

    explicit Country(std::string name_, country_id);

    const std::string& getName();

    explicit Country(nlohmann::json);
    nlohmann::json get_json();

    std::shared_ptr<CountryCitizen> getCitizenManager() { return citizen; }

private:
    std::string name;
    std::shared_ptr<CountryCitizen> citizen;
};
}

#endif  // TES_COUNTRY_HEADER_COUNTRY_COUNTRY_HPP_
