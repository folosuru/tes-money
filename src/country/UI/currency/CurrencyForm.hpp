#pragma once
#ifndef TES_COUNTRY_SRC_UI_CURRENCY_CURRENCYFORM_HPP_
#define TES_COUNTRY_SRC_UI_CURRENCY_CURRENCYFORM_HPP_
#include <llapi/mc/Player.hpp>
#include <DataManager.hpp>
#include <country/Country.hpp>
#include "CppArrai18n/Arrai18n.hpp"

namespace tes::UI::CountryForm {

void currencySetting(Player *player,
                     const std::shared_ptr<Citizen>&,
                     const std::shared_ptr<DataManager>&);

void createCurrency(Player *player,
                    const std::shared_ptr<Citizen>&,
                    const std::shared_ptr<DataManager>&,
                    std::optional<Arrai18n::trl_text> error_message = std::nullopt);

void editCurrency(Player *player,
                  const std::shared_ptr<Citizen>&,
                  const std::shared_ptr<DataManager>&);

void editMoneyAddTrigger(Player *player,
                         const std::shared_ptr<Citizen>&,
                         const std::shared_ptr<DataManager>&);
}

#endif //TES_COUNTRY_SRC_UI_CURRENCY_CURRENCYFORM_HPP_
