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
#include <util/player_identify/PlayerIdentify.hpp>
#include <util/player_identify/PlayerIdentifyProvider.hpp>
#include <util/dll_declspec.hpp>

namespace tes {
class CountryManager;
class TES_DLL CitizenRefer {
public:
    explicit CitizenRefer(std::shared_ptr<PlayerIdentifyProvider>);

    std::shared_ptr<Citizen> get(const PlayerIdentify&);
    std::shared_ptr<Citizen> get(Types::player_name_view);

    void add(const std::shared_ptr<Citizen>&);

    void remove(const PlayerIdentify&);

    static std::shared_ptr<CitizenRefer> load(const std::shared_ptr<CountryManager>&,
                                              const std::shared_ptr<PermissionManager>&,
                                              const std::shared_ptr<PlayerIdentifyProvider>&);


private:
    std::unordered_map<PlayerIdentify, std::shared_ptr<Citizen>> citizen;
    const std::shared_ptr<PlayerIdentifyProvider> identify_provider;
};
}
#endif  // TES_HEADER_COUNTRY_CITIZEN_CITIZENREFER_HPP_
