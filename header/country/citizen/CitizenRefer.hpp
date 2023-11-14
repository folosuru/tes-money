#pragma once
#ifndef TES_HEADER_COUNTRY_CITIZEN_CITIZENREFER_HPP_
#define TES_HEADER_COUNTRY_CITIZEN_CITIZENREFER_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <types/GeneralTypes.hpp>
#include <country/citizen/Citizen.hpp>
#include <country/CountryManager.hpp>
#include <misc/PermissionManager.hpp>
#include <util/dll_declspec.hpp>

namespace tes {
class CountryManager;
class TES_DLL CitizenRefer {
public:
    CitizenRefer() = default;

    CitizenRefer(const std::shared_ptr<CountryManager>&,
                 const std::shared_ptr<PermissionManager>&);

    std::shared_ptr<Citizen> get(Types::player_name_view);

    void add(const std::shared_ptr<Citizen>&);

    void loadCitizen(const std::shared_ptr<CountryManager>&,
                     const std::shared_ptr<PermissionManager>&);


private:
    std::unordered_map<Types::player_name, std::shared_ptr<Citizen>> citizen;
};
}
#endif  // TES_HEADER_COUNTRY_CITIZEN_CITIZENREFER_HPP_
