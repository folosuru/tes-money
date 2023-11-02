#pragma once
#ifndef TES_MONEY_COUNTRY_SRC_UI_GENERAL_HPP_
#define TES_MONEY_COUNTRY_SRC_UI_GENERAL_HPP_
#include <functional>
#include <string>
#include <memory>
#include <llapi/mc/Player.hpp>
#include <DataManager.hpp>
#include <country/Country.hpp>

namespace tes::UI::CountryForm {
    void countryMenu(Player *, const std::shared_ptr<DataManager>&);

    void countryJoinedMenu(Player*,
                           const std::shared_ptr<Citizen>&,
                           const std::shared_ptr<DataManager>&);

    void countryNotJoinedMenu(Player *);
}
#endif  // TES_MONEY_COUNTRY_SRC_UI_GENERAL_HPP_
