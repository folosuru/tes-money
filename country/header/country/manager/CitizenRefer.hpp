#pragma once
#ifndef TES_COUNTRY_COUNTRY_HEADER_REFER_CITIZENREFER_HPP_
#define TES_COUNTRY_COUNTRY_HEADER_REFER_CITIZENREFER_HPP_
#include "../citizen/Citizen.hpp"
#include <unordered_map>
#include <memory>
#include <util/GeneralTypes.hpp>
#include "../util/dll_declspec.hpp"

namespace tes {
class TES_COUNTRY_DLL CitizenRefer {
public:
    std::shared_ptr<Citizen> get(Types::player_name_view);

    void add(const std::shared_ptr<Citizen>&);


private:
    std::unordered_map<Types::player_name, std::shared_ptr<Citizen>> citizen;
};
}
#endif  // TES_COUNTRY_COUNTRY_HEADER_REFER_CITIZENREFER_HPP_
