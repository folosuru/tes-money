#pragma once
#ifndef TES_COUNTRY_HEADER_CITIZEN_CITIZEN_HPP_
#define TES_COUNTRY_HEADER_CITIZEN_CITIZEN_HPP_
#include "../country/Country.hpp"
#include "../manager/CitizenRefer.hpp"
#include "Perimission.hpp"
#include <memory>
#include <unordered_set>
namespace tes {
class Citizen {
public:
    const std::string name;

    Citizen(const std::shared_ptr<CitizenRefer>&, const std::shared_ptr<Country>&, std::string name);

    bool hasPermission(Permission);

    void addPermission(Permission);

    void removePermission(Permission);

private:
    std::shared_ptr<Country> country;
    std::unordered_set<Permission> permission;
};
}
#endif  // TES_COUNTRY_HEADER_CITIZEN_CITIZEN_HPP_
