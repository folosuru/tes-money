#include <country/economy/CountryEconomy.hpp>
#include <money/player/PlayerManager.hpp>
#include <country/Country.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include "util/Resources.hpp"
#include <types/MoneyTypes.hpp>
#include <memory>
#include <utility>
#include <AsyncTask/TaskManager.hpp>
#include "task/TriggerUpssetTask.hpp"
#include "task/CurrencyRegistrationTask.hpp"
#include "task/TriggerRemoveTask.hpp"
namespace tes {

void CountryEconomy::runTrigger(const MoneyAddTriggerKey& trigger_name, std::shared_ptr<PlayerMoney> player) noexcept {
    if (money_add_trigger.contains(trigger_name)) {
        player->add(Money(money_add_trigger.at(trigger_name), currency.lock()));
    }
}

std::shared_ptr<Currency> CountryEconomy::getCurrency() {
    return currency.lock();
}

void CountryEconomy::setCurrency(const std::shared_ptr<Currency>& new_cur) {
    currency = new_cur;
    AsyncTask::add_task(std::make_shared<task::CurrencyRegistrationTask>(new_cur->currency_name, country.id));
}

Types::money_value_t CountryEconomy::getValue(const MoneyAddTriggerKey& trigger_name) {
    return money_add_trigger.at(trigger_name);
}

bool CountryEconomy::existsTrigger(const MoneyAddTriggerKey& name) const noexcept {
    return money_add_trigger.contains(name);
}

void CountryEconomy::updateTrigger(const MoneyAddTriggerKey& trigger_name, int value) {
    if (value <= 0) return;
    money_add_trigger[trigger_name] = value;
    AsyncTask::add_task(std::make_shared<task::TriggerUpsertTask>(*trigger_name, value, country.id));
}

void CountryEconomy::removeTrigger(const MoneyAddTriggerKey& trigger_name) {
    if (money_add_trigger.contains(trigger_name)) {
        money_add_trigger.erase(trigger_name);
        AsyncTask::add_task(std::make_shared<task::TriggerRemoveTask>(*trigger_name, country.id));
    }
}

std::shared_ptr<CountryEconomy> CountryEconomy::load(const Country& country,
                                                     const std::shared_ptr<MoneyAddTriggerManager>& trigger_mng,
                                                     const std::shared_ptr<CurrencyManager>& currency_mng) {
    SQLite::Database db = getCountryDB();
    SQLite::Statement query(db, R"(SELECT trigger, add_value from country_money_trigger where country = ?;)");
    query.bind(1, country.id);
    std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> triggers;
    while (query.executeStep()) {
        std::string trigger = query.getColumn(0).getString();
        Types::money_value_t value = query.getColumn(1);
        triggers.insert({trigger_mng->getKey(trigger), value});
    }
    SQLite::Statement getCurrencyQuery(db, R"(select currency from country where id=?)");
    getCurrencyQuery.bind(1, country.id);
    getCurrencyQuery.executeStep();
    if (getCurrencyQuery.executeStep()) {
        std::shared_ptr<Currency> currency = currency_mng->getCurrency(getCurrencyQuery.getColumn(0));
        return std::shared_ptr<CountryEconomy>(new CountryEconomy(triggers, currency, country));
    }
    return std::shared_ptr<CountryEconomy>(new CountryEconomy(triggers, country));
}

CountryEconomy::CountryEconomy(std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> trigger,
                               const Country& country) :
    money_add_trigger(std::move(trigger)), country(country) {}

CountryEconomy::CountryEconomy(std::unordered_map<MoneyAddTriggerKey, Types::money_value_t> trigger,
                               std::weak_ptr<Currency> currency,
                               const Country& country) :
    money_add_trigger(std::move(trigger)), currency(std::move(currency)), country(country) {}

CountryEconomy::CountryEconomy(const Country& country)
: country(country){

}

}
