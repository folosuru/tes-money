#pragma once
#ifndef TES_COUNTRY_HEADER_CITIZEN_CITIZEN_HPP_
#define TES_COUNTRY_HEADER_CITIZEN_CITIZEN_HPP_
#include "../country/Country.hpp"
#include "Perimission.hpp"
#include <memory>
namespace tes {
class Citizen {
public:
    Citizen(std::shared_ptr<Country>);

    bool hasPermission();

    void addPermission(Permission);

    void removePermission(Permission);

private:
    std::shared_ptr<Country> country;
    std::vector<Permission> permission;
};
}
#endif  // TES_COUNTRY_HEADER_CITIZEN_CITIZEN_HPP_
