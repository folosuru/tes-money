#include <country/economy/CountryEconomy.hpp>
#include <money/player/PlayerManager.hpp>
#include <country/Country.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include "util/Resources.hpp"
#include <types/MoneyTypes.hpp>

namespace tes {

void CountryEconomy::runTrigger(std::string_view trigger_name, const std::string& player_name) noexcept {
    if (money_add_trigger.contains(trigger_name)) {
        PlayerManager::get()->getPlayer(player_name)
            ->add(Money(money_add_trigger.at(trigger_name), currency.lock()));
    }
}
/**
 * JSONから読み込む？どっちがいいかな
 */
 // TODO: nullチェックいる？
std::shared_ptr<CountryEconomy> CountryEconomy::load(nlohmann::json json) {
    std::weak_ptr<Currency> cur(CurrencyManager::get()->getCurrency(json["currency"].get<std::string>()));
    std::unordered_map<std::string_view, int> triggers;
    for (const auto& i : json["trigger"].items()) {
        triggers.insert({i.key(),i.value()});
    }
    return std::shared_ptr<CountryEconomy>(new CountryEconomy(triggers,cur));
}


std::shared_ptr<Currency> CountryEconomy::getCurrency() {
    return currency.lock();
}

void CountryEconomy::setCurrency(const std::shared_ptr<Currency>& new_cur) {
    currency = new_cur;
}

int CountryEconomy::getValue(const std::string& trigger_name) {
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

std::shared_ptr<CountryEconomy> CountryEconomy::load(std::shared_ptr<Country> country) {
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement query(db, R"(SELECT trigger, add_value from country_money_trigger where country = ?;)");
    query.bind(1, country->id);
    while (query.executeStep()) {
        std::string trigger = query.getColumn(0).getString();
        Types::money_value_t value = query.getColumn(1);

    }
//    static_assert(false, "todo");
    return std::shared_ptr<CountryEconomy>();
}
}
