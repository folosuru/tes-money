#pragma once
#ifndef TES_COUNTRY_COUNTRY_HEADER_REFER_CITIZENREFER_HPP_
#define TES_COUNTRY_COUNTRY_HEADER_REFER_CITIZENREFER_HPP_

#include <unordered_map>
#include <memory>
#include <types/GeneralTypes.hpp>
#include "../citizen/Citizen.hpp"
#include "CountryManager.hpp"
#include "../permission/PermissionManager.hpp"
#include "../util/dll_declspec.hpp"

namespace tes {
class TES_COUNTRY_DLL CitizenRefer {
public:
    std::shared_ptr<Citizen> get(Types::player_name_view);

    void add(const std::shared_ptr<Citizen>&);

    void loadCitizen(std::shared_ptr<CountryManager>,
                     std::shared_ptr<PermissionManager>);


private:
    std::unordered_map<Types::player_name, std::shared_ptr<Citizen>> citizen;
    const inline static std::string db_name = "country.sqlite";
};
}
#endif  // TES_COUNTRY_COUNTRY_HEADER_REFER_CITIZENREFER_HPP_
