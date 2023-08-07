#include <iostream>
#include <stdexcept>
#include "../src/header/api.hpp"

void checkLoadJson() {
    std::shared_ptr<tes::CurrencyManager> currency = std::make_shared<tes::CurrencyManager>();
    currency->addCurrency(std::make_shared<tes::Currency>("JPY"));
    currency->addCurrency(std::make_shared<tes::Currency>("ACP"));

    auto money = tes::PlayerMoney(
        nlohmann::json::parse(R"({"money" : { "JPY" : 130, "ACP" : 254 }})"),
        currency);
    if (money.get(currency->getCurrency("jpy"))->value != 130 ||
        money.get(currency->getCurrency("acp"))->value != 254) {
        std::cout << "load json failed" << std::endl;
        throw std::exception("");
    }
}

int main() {
    checkLoadJson();
    std::shared_ptr<tes::PlayerManager> player_manager = tes::getPlayerManager();
    std::shared_ptr<tes::CurrencyManager> currency_manager = tes::getCurrencyManager();

    {
        bool check_unknown_player_access = false;
        try {
            std::shared_ptr<tes::PlayerMoney> money1 = player_manager->getPlayer("Yamada");
        } catch (std::invalid_argument& e) {
            check_unknown_player_access = true;
        }
        if (!check_unknown_player_access) {
            return 1;
        }
    }

    {
        bool check_unknown_currency_access = false;
        try {
            currency_manager->getCurrency("JPY");
        } catch (std::invalid_argument& e) {
            check_unknown_currency_access = true;
        }
        if (!check_unknown_currency_access) {
            return 1;
        }
    }
    player_manager->addPlayer("Yoshida", std::make_shared<tes::PlayerMoney>());
    std::shared_ptr<tes::PlayerMoney> money = player_manager->getPlayer("Yoshida");

    currency_manager->addCurrency(std::make_shared<tes::Currency>("JPY"));

    std::shared_ptr<tes::Currency> cur = currency_manager->getCurrency("jpY");

    {
        money->add(tes::Money(100, cur));
        if (money->get(cur)->value != 100) {
            return 1;
        }
    }

    {
        money->remove(tes::Money(50, cur));
        if (money->get(cur)->value != 50) {
            return 1;
        }
    }

    player_manager->addPlayer("Shinada", std::make_shared<tes::PlayerMoney>());
    std::shared_ptr<tes::PlayerMoney> money2 = player_manager->getPlayer("Shinada");
    {
        money->send(money2, tes::Money(10, cur));
        if (money->get(cur)->value != 40) {
            return 1;
        }
        if (money2->get(cur)->value != 10) {
            return 1;
        }
    }
    return 0;
}
