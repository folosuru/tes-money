#include <country/economy/CountryEconomy.hpp>
#include <money/player/PlayerManager.hpp>
#include <country/Country.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include "util/Resources.hpp"
#include <types/MoneyTypes.hpp>
#include <memory>

namespace tes {

void CountryEconomy::runTrigger(std::string_view trigger_name, std::shared_ptr<PlayerMoney> player) noexcept {
    if (money_add_trigger.contains(trigger_name)) {
        player->add(Money(money_add_trigger.at(trigger_name), currency.lock()));
    }
}

std::shared_ptr<Currency> CountryEconomy::getCurrency() {
    return currency.lock();
}

void CountryEconomy::setCurrency(const std::shared_ptr<Currency>& new_cur) {
    currency = new_cur;
}

Types::money_value_t CountryEconomy::getValue(const std::string& trigger_name) {
    return money_add_trigger.at(trigger_name);
}

bool CountryEconomy::existsTrigger(const std::string& name) const noexcept {
    return money_add_trigger.contains(name);
}

void CountryEconomy::updateTrigger(const std::string& trigger_name, int value) {
    if (value <= 0) return;
    money_add_trigger[trigger_name] = value;
}

void CountryEconomy::removeTrigger(const std::string& trigger_name) {
    if (money_add_trigger.contains(trigger_name)) {
        money_add_trigger.erase(trigger_name);
    }

}

std::shared_ptr<CountryEconomy> CountryEconomy::load(int country_id,
                                                     const std::shared_ptr<MoneyAddTriggerManager>& trigger_mng,
                                                     const std::shared_ptr<CurrencyManager>& currency_mng) {
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement query(db, R"(SELECT trigger, add_value from country_money_trigger where country = ?;)");
    query.bind(1, country_id);
    std::unordered_map<std::string_view, Types::money_value_t> triggers;
    while (query.executeStep()) {
        std::string trigger = query.getColumn(0).getString();
        Types::money_value_t value = query.getColumn(1);
        triggers.insert({trigger_mng->getOrGenKey(trigger), value});
    }
    SQLite::Statement getCurrencyQuery(db, R"(select currency from country where id=?)");
    getCurrencyQuery.bind(1, country_id);
    getCurrencyQuery.executeStep();
    std::shared_ptr<Currency> currency = currency_mng->getCurrency(getCurrencyQuery.getColumn(0));
    return std::shared_ptr<CountryEconomy>(new CountryEconomy(triggers, currency, trigger_mng));
}
}
