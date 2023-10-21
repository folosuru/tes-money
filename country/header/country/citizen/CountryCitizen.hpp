#pragma once
#ifndef TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
#define TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
#include <string>
#include <unordered_map>
#include <memory>
#include <util/GeneralTypes.hpp>
#include "Citizen.hpp"
#include "../util/dll_declspec.hpp"

namespace tes {
class Citizen;
class TES_COUNTRY_DLL CountryCitizen {
public:
    std::shared_ptr<Citizen> getCitizen(Types::player_name_view);

    void add(Types::player_name_view);
    void add(Types::player_name_view, std::shared_ptr<Citizen>);

    void ban(Types::player_name_view);

    void loadAll();

private:
    std::unordered_map<Types::player_name, std::shared_ptr<Citizen>> citizen;
};
}
#endif  // TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
