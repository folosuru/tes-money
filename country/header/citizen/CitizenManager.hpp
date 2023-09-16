#pragma once
#ifndef TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
#define TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
#include <string>
#include <unordered_map>
#include "Citizen.hpp"
#include <memory>
#include <Util/types.hpp>

namespace tes {
class CitizenManager {
public:

    std::shared_ptr<Citizen> getCitizen(Types::player_name_view);

    void add();

    void ban();

private:
    std::unordered_map<Types::player_name,std::shared_ptr<Citizen>> citizen;
};
}
#endif  // TES_COUNTRY_HEADER_CITIZEN_CITIZENMANAGER_HPP_
