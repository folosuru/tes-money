#include <iostream>
#include <stdexcept>
#include <fstream>
#include <player/PlayerManager.hpp>
#include <currency/CurrencyManager.hpp>
#include <cpptf/Cpptf.hpp>


void checkLoadJson() {
    std::shared_ptr<tes::CurrencyManager> currency;
    currency = std::make_shared<tes::CurrencyManager>();
    currency->addCurrency(std::make_shared<tes::Currency>(std::string("JPY")));
    currency->addCurrency(std::make_shared<tes::Currency>(std::string("ACP")));
    std::string json_t = R"({"money" : { "JPY" : 130, "ACP" : 254 }})";
    auto json = nlohmann::json::parse(json_t);
    auto money = tes::PlayerMoney(json, currency);
    cpptf::isTrue("json_load", money.get(currency->getCurrency("jpy")).value == 130 &&
                               money.get(currency->getCurrency("acp")).value == 254);
}

void PlayerMng() {
    cpptf::change_section("PlayerManager");
    cpptf::except_any("unknown player access", [](){
        tes::PlayerManager(std::make_shared<tes::CurrencyManager>()).getPlayer("Yoshida");
    });
    cpptf::isSame("player money access", []() {
        auto mng = tes::PlayerManager(std::make_shared<tes::CurrencyManager>());
        auto m = std::make_shared<tes::PlayerMoney>();
        mng.addPlayer("Taro", m);
        auto currency = std::make_shared<tes::Currency>(std::string("jpy"));
        m->add(tes::Money(100, currency));
        return mng.getPlayer("Taro")->get(currency).value;
    }(), 100);
    checkLoadJson();
}

void PlayerMoney() {
    cpptf::change_section("PlayerMoney");
    std::shared_ptr<tes::CurrencyManager> currency_manager = std::make_shared<tes::CurrencyManager>();
    std::shared_ptr<tes::PlayerManager> player_manager = std::make_shared<tes::PlayerManager>(currency_manager);
    player_manager->addPlayer("Yoshida", std::make_shared<tes::PlayerMoney>());
    std::shared_ptr<tes::PlayerMoney> money = player_manager->getPlayer("Yoshida");
    currency_manager->addCurrency(std::make_shared<tes::Currency>(std::string("JPY")));

    std::shared_ptr<tes::Currency> cur = currency_manager->getCurrency("jpY");

    money->add(tes::Money(100, cur));
    cpptf::isSame("add money", money->get(cur), tes::Money(100, cur));

    money->remove(tes::Money(50, cur));
    cpptf::isSame("remove money", money->get(cur), tes::Money(50, cur));

    player_manager->addPlayer("Shinada", std::make_shared<tes::PlayerMoney>());
    std::shared_ptr<tes::PlayerMoney> money2 = player_manager->getPlayer("Shinada");

    money->send(money2, tes::Money(10, cur));
    cpptf::isSame("send from", money->get(cur), tes::Money(40, cur));
    cpptf::isSame("send from", money2->get(cur), tes::Money(10, cur));
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
    const auto currency1 = std::make_shared<tes::Currency>(std::string("currency_1"));
    const auto currency2 = std::make_shared<tes::Currency>(std::string("currency_2"));
    cpptf::except_any("validation", [currency1](){tes::Money(-100, currency1);});
    cpptf::isSame("operator ==", tes::Money(100, currency1), tes::Money(100, currency1));
    cpptf::isTrue("operator ==", [currency1, currency2]() {
        return !(tes::Money(100, currency1) == tes::Money(100, currency2));
    }());
    cpptf::isTrue("operator ==", [currency1]() {
        return !(tes::Money(100, currency1) == tes::Money(150, currency1));
    }());
    cpptf::isTrue("operator ==", [currency1, currency2]() {
        return !(tes::Money(100, currency1) == tes::Money(150, currency2));
    }());

    cpptf::isSame("add", tes::Money(100, currency1) + tes::Money(75, currency1), tes::Money(175, currency1));
    cpptf::except_any("add other currency", [currency1, currency2]() {
        tes::Money(100, currency1) + (tes::Money(200, currency2));
    });
    cpptf::isSame("remove", tes::Money(500, currency1) - tes::Money(75, currency1), tes::Money(425, currency1));
    cpptf::except_any("money under 0", [currency1]() {
        tes::Money(100, currency1) - (tes::Money(200, currency1));
    });
}

int main() {
    money();
    PlayerMng();
    CurrencyMng::checkUnknownAccess();
    PlayerMoney();
    cpptf::complete();
    return 0;
}
