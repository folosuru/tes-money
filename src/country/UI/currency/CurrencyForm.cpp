#ifndef DEBUG_WITHOUT_LLAPI
#include "CurrencyForm.hpp"
#include <llapi/FormUI.h>
#include <CppArrai18n/Arrai18n_def.hpp>
#include <currency/CurrencyManager.hpp>
#include <util/Resources.hpp>
#include <utility>
#include <functional>
namespace tes::UI::CountryForm {

void currencySetting(Player *player,
                     const std::shared_ptr<Citizen>& citizen,
                     const std::shared_ptr<DataManager>& data) {
    if (!citizen->hasPermission(country_permission::currency) && !citizen->hasPermission(country_permission::any)) {
        return;
    }
    if (!citizen->getCountry()->getEconomyManager()->getCurrency()) {
        createCurrency(player, citizen, data);
    } else {
        editCurrency(player, citizen, data);
    }
}

/*
|     create currency     |
|-------------------------|
| "JPY" is already exists!|  optional
| |---------------------| |
| | currency name input | |
| |---------------------| |
| name should be easy to  |
| call.                   |
| |---------------------| |
| |    send     button  | |
| |---------------------| |
|-------------------------|
*/
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
    form.sendTo(player, [manager, citizen](Player *player, auto result) {
        if (result.empty()) return;

        std::string name = result["currency_name"]->getString();
        auto validation = DataManager::get()->CurrencyMng->currencyNameValidation(name);
        if (validation) {
            std::shared_ptr<Currency> new_currency = std::make_shared<Currency>(name);
            DataManager::get()->CurrencyMng->addCurrency(new_currency);
            citizen->getCountry()->getEconomyManager()->setCurrency(new_currency);
            player->sendText(Arrai18n::trl(player->getLanguageCode(),
                                           "country.currency.create.success",
                                           {name}));
        } else {
            createCurrency(player, citizen, manager, validation.get_fail());
        }

    });
}

namespace {
std::string getTriggerValueText(const std::shared_ptr<CountryEconomy>& economy, const MoneyAddTriggerKey& trigger) {
    if (economy->existsTrigger(trigger)) {
        return std::to_string(economy->getValue(trigger));
    }
    return "0";
}

const std::string trigger_wood_break = "WoodBreak";
const std::string trigger_stone_break = "StoneBreak";

}

void editCurrency(Player *player,
                  const std::shared_ptr<Citizen>& citizen,
                  const std::shared_ptr<DataManager>& mng) {
    std::shared_ptr<CountryEconomy> economy = citizen->getCountry()->economy;
    editMoneyAddTrigger(player, citizen, mng);

}

namespace {
/*
| edit money add trigger  |
|-------------------------|
| on Dirt break     =||   | toggle
|                         |
| |---------------------| |
| | get value           | | input
| |---------------------| |
|                         |
| on Sand break     ||=   | toggle
|                         |
| |---------------------| |
| | get value           | | input
| |---------------------| |
|                         |
            .
            .
            .
*/

void showTriggerSettingForm(const std::shared_ptr<CountryEconomy>& economy,
                            const std::shared_ptr<MoneyAddTriggerCategory>& category,
                            Player *pl,
                            const std::function<void(void)>& callback) {
    Form::CustomForm form("");
    for (const auto& trigger : category->Child) {
        form.addToggle("enable_" + *trigger,
                       Arrai18n::trl(pl->getLanguageCode(),
                                     "country.currency.trigger." + *trigger + ".description"),
                       economy->existsTrigger(trigger));
        form.addInput(*trigger + "_trigger_value",
                      Arrai18n::trl(pl->getLanguageCode(),
                                    "country.currency.trigger.get_value"),
                      getTriggerValueText(economy, trigger));
    }

    form.sendTo(pl, [category, economy, callback](Player *player,
                                                  std::map<string, std::shared_ptr<Form::CustomFormElement>> result) {
        if (result.empty()) {
            callback();
            return;
        }
        for (const auto& trigger : category->Child) {
            if (result["enable_" + *trigger]->getBool()) {
                try {
                    int value = std::stoi(result[*trigger + "_trigger_value"]->getString());
                    if (value <= 0) {
                        continue;
                    }
                    economy->updateTrigger(trigger, value);
                } catch (...) {
                    continue;
                }
            } else {
                economy->removeTrigger(trigger);
            }
        }
        callback();
    });
}
}

/*
| edit money add trigger  |
|-------------------------|
| you can set add money   |
| when brock break...     |
| |---------------------| |
| | surface block break | | button
| |---------------------| |
|                         |
| |---------------------| |
| | Ore block break     | | button
| |---------------------| |
            .
            .
            .
*/
void editMoneyAddTrigger(Player *player,
                         const std::shared_ptr<Citizen>& citizen,
                         const std::shared_ptr<DataManager>& data) {
    std::shared_ptr<CountryEconomy> economy = citizen->getCountry()->economy;
    Form::SimpleForm form("", Arrai18n::trl(player->getLanguageCode(),
                                            "country.currency.trigger.description"));
    for (const auto& category : data->MoneyAddTriggerMng->getAllWithCategory()) {
        form.addButton(Arrai18n::trl(player->getLanguageCode(), "country.currency.trigger.category." + category->name),
                       "", [=](Player *pl) {
                showTriggerSettingForm(economy, category, pl, [=]() {
                    editMoneyAddTrigger(player, citizen, data);
                });
            });
    }
    form.sendTo(player);
}
}
#endif