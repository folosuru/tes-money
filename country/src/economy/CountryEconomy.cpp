#include <economy/CountryEconomy.hpp>
#include <money/player/PlayerManager.hpp>
namespace tes {
void CountryEconomy::runTrigger(std::string trigger_name, std::string player_name) {
    if (money_add_trigger.contains(trigger_name)) {
        PlayerManager::get()->getPlayer(player_name)
            ->add(Money(money_add_trigger.at(trigger_name), currency.lock());
    }
}
/**
 * JSONから読み込む？どっちがいいかな
 */
 // TODO: nullチェックいる？
std::shared_ptr<CountryEconomy> load(nlohmann::json json) {
    std::shared_ptr<Currency> cur = CurrencyManager::get()->getCurrency(json["currency"].get<std::string>());
    std::unordered_map<std::string_view, int> triggers;
    for (cons auto& i : json["trigger"].items()) {
        triggers.insert({i.key(),i.value()});
    }
    return std::make_shared<CountryEconomy>(triggers,cur);
}


const std::shared_ptr<Currency>& CountryEconomy::getCurrency() {
    return currency;
}

void CountryEconomy::setCurrency(std::shared_ptr<Currency> new_cur) {
    currency = new_cur;
}
}
