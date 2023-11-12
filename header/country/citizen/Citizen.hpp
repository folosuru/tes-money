#pragma once
#ifndef TES_HEADER_COUNTRY_CITIZEN_CITIZEN_HPP_
#define TES_HEADER_COUNTRY_CITIZEN_CITIZEN_HPP_
#include <country/citizen/permission/Perimission.hpp>
#include <memory>
#include <unordered_set>
#include <string>
#include <util/dll_declspec.hpp>

namespace tes {
class Country;
class CitizenRefer;
class TES_DLL Citizen {
public:
    const std::string name;

    static std::shared_ptr<Citizen> build(const std::shared_ptr<CitizenRefer>&,
                                          const std::shared_ptr<Country>&,
                                          std::string name,
                                          std::unordered_set<Permission> permission_);
    static std::shared_ptr<Citizen> build(const std::shared_ptr<CitizenRefer>&,
                                          const std::shared_ptr<Country>&,
                                          std::string name);

    bool hasPermission(Permission);

    void addPermission(Permission);

    void removePermission(Permission);

    [[nodiscard]]
    const std::unordered_set<Permission>& getAllPermission() const noexcept;

    [[nodiscard]]
    std::shared_ptr<Country> getCountry() const;

    void save();

private:
    Citizen(const std::shared_ptr<Country>&,
            std::string name);

    Citizen(const std::shared_ptr<Country>&,
            std::string name,
            std::unordered_set<Permission> permission_);

    std::weak_ptr<Country> country;

    std::unordered_set<Permission> permission;
};
}
#endif  // TES_HEADER_COUNTRY_CITIZEN_CITZEN_HPP_
