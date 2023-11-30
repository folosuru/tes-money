#pragma once
#ifndef TES_HEADER_COUNTRY_CITIZEN_CITIZENMANAGER_HPP_
#define TES_HEADER_COUNTRY_CITIZEN_CITIZENMANAGER_HPP_
#include <string>
#include <unordered_map>
#include <memory>
#include <types/GeneralTypes.hpp>
#include <country/citizen/Citizen.hpp>
#include <util/player_identify/PlayerIdentify.hpp>
#include <util/dll_declspec.hpp>

namespace tes {
class Citizen;
class TES_DLL CountryCitizen {
public:
    std::shared_ptr<Citizen> getCitizen(const PlayerIdentify&);

    ~CountryCitizen() = default;

    void add(const std::shared_ptr<Citizen>&, bool writeDB = true);

    void ban(const PlayerIdentify& name);

    [[nodiscard]] size_t getCitizenCount() const noexcept;

private:
    std::unordered_map<PlayerIdentify, std::shared_ptr<Citizen>> citizens;

};
}
#endif  // TES_HEADER_COUNTRY_CITIZEN_CITIZENMANAGER_HPP_
