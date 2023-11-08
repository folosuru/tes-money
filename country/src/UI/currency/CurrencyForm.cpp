#include "CurrencyForm.hpp"
#include <llapi/FormUI.h>
#include <CppArrai18n/Arrai18n.hpp>
#include <money/currency/CurrencyManager.hpp>
#include <util/Resources.hpp>
#include <utility>
namespace tes::UI::CountryForm {

void currencySetting(Player* player,
                     const std::shared_ptr<Citizen>& citizen,
                     const std::shared_ptr<DataManager>& data) {
    if (!citizen->hasPermission(country_permission::currency)) {
        return;
    }
    if (!citizen->getCountry()->getEconomyManager()->getCurrency()) {
        createCurrency(player, citizen, data);
    } else {
        editCurrency(player, citizen, data);
    }
}

void createCurrency(Player *player,
                    const std::shared_ptr<Citizen>& citizen,
                    const std::shared_ptr<DataManager>& manager,
                    std::optional<Arrai18n::trl_text> error_message) {
    Form::CustomForm form(Arrai18n::trl(player->getLanguageCode(),
                                        "country.form.currency.create"));
    if (error_message) {
        form.addLabel("error_label", Arrai18n::trl(player->getLanguageCode(),
                                                   error_message.value()));
    }
    form.addInput("currency_name",
                  Arrai18n::trl(player->getLanguageCode(),
                                "country.form.currency.name"));
    form.addLabel("label",
                  Arrai18n::trl(player->getLanguageCode(),
                                "country.form.currency.create.info"));
    form.sendTo(player, [manager, citizen](Player* player, auto result){
        if (result.empty()) return;

        std::string name = result["currency_name"]->getString();
        auto validation = CurrencyManager::get()->currencyNameValidation(name);
        if (validation) {
            std::shared_ptr<Currency> new_currency = std::make_shared<Currency>(name);
            CurrencyManager::get()->addCurrency(new_currency);
            citizen->getCountry()->getEconomyManager()->setCurrency(new_currency);
            player->sendText(Arrai18n::trl(player->getLanguageCode(),
                                           "country.currency.create.success",
                                           {name}));
        } else {
            createCurrency(player, citizen, manager, validation.get_fail());
        }

    });
}

void editCurrency(Player *player,
                  const std::shared_ptr<Citizen>& citizen,
                  const std::shared_ptr<DataManager>& mng) {
    Form::CustomForm form(Arrai18n::trl(player->getLanguageCode(),
                                        "country.form.top.currency"));
    form.addLabel("label1", Arrai18n::trl(player->getLanguageCode(),
                                          "country.currency.trigger.description"));
    form.addToggle("enable_Woodbreak_trigger",
                   Arrai18n::trl(player->getLanguageCode(),
                                 "country.currency.trigger.WoodBreak.description"),
                   citizen->getCountry()->economy->existsTrigger(""));
    form.addInput("WoodBreak_trigger_value",
                  Arrai18n::trl(player->getLanguageCode(),
                                "country.currency.trigger.get_value"));

    form.addToggle("enable_Stonebreak_trigger",
                   Arrai18n::trl(player->getLanguageCode(),
                   "country.currency.trigger.StoneBreak.description"));
    form.addInput("StoneBreak_trigger_value",
                  Arrai18n::trl(player->getLanguageCode(),
                                "country.currency.trigger.get_value"));

}
}
