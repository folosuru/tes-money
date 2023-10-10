#pragma once
#ifndef TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
#define TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
#include <string>
#include <unordered_map>
#include <memory>
#include <Util/types.hpp>
#include "Citizen.hpp"

namespace tes {
class Citizen;
class TES_COUNTRY_DLL CitizenManager {
public:

    std::shared_ptr<Citizen> getCitizen(Types::player_name_view);

    void add(Types::player_name_view);
    void add(Types::player_name_view, std::shared_ptr<Citizen>);

    void ban(Types::player_name_view);

private:
    std::unordered_map<Types::player_name,std::shared_ptr<Citizen>> citizen;
};
}
#endif  // TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
