#include <iostream>
#include <stdexcept>
#include <fstream>
#include <player/PlayerManager.hpp>
#include <currency/CurrencyManager.hpp>
#include <Cpptf.hpp>


void checkLoadJson() {
    std::shared_ptr<tes::CurrencyManager> currency;
    currency = std::make_shared<tes::CurrencyManager>();
    currency->addCurrency(std::make_shared<tes::Currency>(std::string("JPY")));
    currency->addCurrency(std::make_shared<tes::Currency>(std::string("ACP")));
    std::string json_t = R"({"money" : { "JPY" : 130, "ACP" : 254 }})";
    auto json = nlohmann::json::parse(json_t);
    auto money = tes::PlayerMoney(json, currency);
    cpptf::isTrue("json_load", money.get(currency->getCurrency("jpy"))->value == 130 &&
                               money.get(currency->getCurrency("acp"))->value == 254);
}

void PlayerMng() {
    cpptf::change_section("PlayerManager");
    cpptf::except_any("unknown player access",[](){
        tes::PlayerManager(std::make_shared<tes::CurrencyManager>()).getPlayer("Yoshida");
    });
    cpptf::isSame("player money access",[](){
        auto mng = tes::PlayerManager(std::make_shared<tes::CurrencyManager>());
        auto m = std::make_shared<tes::PlayerMoney>();
        mng.addPlayer("Taro",m);
        auto currency = std::make_shared<tes::Currency>(std::string("jpy"));
        m->add(tes::Money(100,currency));
        return mng.getPlayer("Taro")->get(currency)->value;
    }(),100);
    checkLoadJson();
}

namespace CurrencyMng {
void checkUnknownAccess() {
    cpptf::except_any("unknown currency access", [](){
        tes::CurrencyManager().getCurrency("ZWL");
    });
}
}

void money() {
    cpptf::change_section("money");
    auto currency = tes::Currency(std::string("currency_1"));

}

int main() {
    PlayerMng();
    CurrencyMng::checkUnknownAccess();
    std::shared_ptr<tes::CurrencyManager> currency_manager = std::make_shared<tes::CurrencyManager>();
    std::shared_ptr<tes::PlayerManager> player_manager = std::make_shared<tes::PlayerManager>(currency_manager);
    player_manager->addPlayer("Yoshida", std::make_shared<tes::PlayerMoney>());
    std::shared_ptr<tes::PlayerMoney> money = player_manager->getPlayer("Yoshida");
    currency_manager->addCurrency(std::make_shared<tes::Currency>(std::string("JPY")));

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
    cpptf::complete();
    return 0;
}
