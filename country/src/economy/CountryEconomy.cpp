#include <economy/CountryEconomy.hpp>
#include <money/player/PlayerManager.hpp>
namespace tes {
void CountryEconomy::runTrigger(std::string trigger_name, std::string player_name) {
    if (money_add_trigger.contains(trigger_name)) {
        PlayerManager::get()->getPlayer(player_name)
            ->add(Money(money_add_trigger.at(trigger_name), currency));
    }
}

const std::shared_ptr<Currency>& CountryEconomy::getCurrency() {
    return currency;
}

void CountryEconomy::setCurrency(std::shared_ptr<Currency> new_cur) {
    currency = new_cur;
}
}