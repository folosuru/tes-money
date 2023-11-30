#ifndef DEBUG_WITHOUT_LLAPI
#include "CountryForm.hpp"
#include <llapi/FormUI.h>
#include <CppArrai18n/Arrai18n_def.hpp>
#include <util/Resources.hpp>
#include <country/citizen/permission/Perimission.hpp>
#include "currency/CurrencyForm.hpp"
#include "join_country/JoinCountry.hpp"

namespace tes::UI::CountryForm {

void countryMenu(Player *player, const std::shared_ptr<DataManager>& data) {
    if (auto citizen = data->CitizenRefer->get(player->getRealName());citizen) {
        countryJoinedMenu(player, citizen, data);
        return;
    } else {
        countryNotJoinedMenu(player);
        return;
    }
}

void countryJoinedMenu(Player *player,
                       const std::shared_ptr<Citizen>& citizen,
                       const std::shared_ptr<DataManager>& data) {
    Form::SimpleForm form("", Arrai18n::trl(player->getLanguageCode(),
                                            "country.form.joined.top",
                                            {citizen->getCountry()->getName()}));
    if (citizen->hasPermission(country_permission::currency) || citizen->hasPermission(country_permission::any)) {  // currency
        form.addButton(Arrai18n::trl(player->getLanguageCode(), "country.form.top.currency"),
                       "", [citizen, data](Player *pl) {
                currencySetting(pl, citizen, data);
            });
    }

    form.addButton(Arrai18n::trl(player->getLanguageCode(), "country.form.top.left"),
                   "", [citizen, data](Player *pl) {
            Form::ModalForm form(Arrai18n::trl(pl->getLanguageCode(),
                                               "country.form.left.title"),
                                 Arrai18n::trl(pl->getLanguageCode(),
                                               "country.form.left.description",
                                               {citizen->getCountry()->getName()}),
                                 Arrai18n::trl(pl->getLanguageCode(), "yes"),
                                 Arrai18n::trl(pl->getLanguageCode(), "no"));

            form.sendTo(pl, [citizen, data](Player *player, bool isConfirm) {
                if (isConfirm) {
                    player->sendText(Arrai18n::trl(player->getLanguageCode(),
                                                   "country.left.complete",
                                                   {citizen->getCountry()->getName()}));
                    citizen->getCountry()->getCitizenManager()->ban(citizen->name);
                    data->CitizenRefer->remove(citizen->name);
                } else {
                    countryJoinedMenu(player, citizen, data);
                }
            });
        });

    form.addButton("Exit");
    form.sendTo(player);
}

void countryNotJoinedMenu(Player *player) {
    Form::SimpleForm form("", "");
    auto data = tes::DataManager::get();
    form.addButton(Arrai18n::trl(player->getLanguageCode(),"country.form.not_joined.look_index")
                   , "", [data](Player *pl) {
        showCountryIndex(pl, data);
    });
    //form.addButton("search country", "", [data](Player *pl) { findCountry(pl, data); });
    form.addButton(Arrai18n::trl(player->getLanguageCode(),"country.form.not_joined.create"), "", [data](Player *pl) {
        createCountry(pl,
                      data->CountryManager,
                      data->player_identify,
                      data->CitizenRefer,
                      data->PermissionManager);
    });
    form.sendTo(player);
}
}
#endif
