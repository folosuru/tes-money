#pragma once
#ifndef TES_HEADER_COUNTRY_CITIZEN_CITIZENMANAGER_HPP_
#define TES_HEADER_COUNTRY_CITIZEN_CITIZENMANAGER_HPP_
#include <string>
#include <unordered_map>
#include <memory>
#include <types/GeneralTypes.hpp>
#include <country/citizen/Citizen.hpp>
#include <util/dll_declspec.hpp>

namespace tes {
class Citizen;
class TES_DLL CountryCitizen {
public:
    std::shared_ptr<Citizen> getCitizen(Types::player_name_view);

    ~CountryCitizen() = default;

    void add(const std::shared_ptr<Citizen>&);

    void ban(Types::player_name_view);

private:
    std::unordered_map<Types::player_name, std::shared_ptr<Citizen>> citizens;
};
}
#endif  // TES_HEADER_COUNTRY_CITIZEN_CITIZENMANAGER_HPP_
