#include <stdexcept>
#include <fstream>
#include <country/Country.hpp>
#include <country/CountryManager.hpp>
#include <country/citizen/CitizenRefer.hpp>
#include <country/citizen/Citizen.hpp>
#include <misc/PermissionManager.hpp>
#include <cpptf/Cpptf.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <misc/money_add_trigger/MoneyAddTriggerManager.hpp>
#include <util/Resources.hpp>

void Citizen_test() {
    using namespace tes;
    cpptf::change_section("Citizen permission");
    std::shared_ptr<PlayerIdentifyProvider> prov = std::make_shared<PlayerIdentifyProvider>();
    std::shared_ptr<tes::CitizenRefer> refer = std::make_shared<tes::CitizenRefer>(prov);
    std::shared_ptr<tes::Country> country = std::make_shared<tes::Country>("Japan", 1);
    std::string_view perm = "foo";
    auto citizen_ = tes::Citizen::build(refer,
                        country,
                        prov->getIdentify("taro"));
    cpptf::isFalse("permission not found", citizen_->hasPermission(perm));
    citizen_->addPermission(perm);
    cpptf::isTrue("permission found", citizen_->hasPermission(perm));
//    citizen_->removePermission(perm);
//    cpptf::isFalse("permission remove", citizen_->hasPermission(perm));
}

void load_citizen() {
    using namespace tes;
    cpptf::change_section("Citizen");
    std::shared_ptr<PlayerIdentifyProvider> prov = std::make_shared<PlayerIdentifyProvider>();
    std::shared_ptr<tes::CitizenRefer> refer = std::make_shared<tes::CitizenRefer>(prov);
    std::shared_ptr<tes::Country> country = std::make_shared<tes::Country>("Japan", 1);
}

void dataLoad_test() {
    cpptf::change_section("dataLoad");
    tes::reset_Database();
    tes::init_Database();
    auto db = tes::getCountryDB();
    /*db.exec("insert into country (id, name, description, currency) values (0,'test-name','test country', 'JPY');");
    db.exec("insert into citizen (name, country) values ('tanaka', 0)");*/
    auto data = tes::DataManager::get();
    cpptf::isSame("get country", data->CountryManager->getCountry(0)->getName(), "test-name");
    cpptf::isSame("get citizen from refer", data->CitizenRefer->get("tanaka")->getCountry(),data->CountryManager->getCountry(0));
    tes::DataManager::get();
    tes::DataManager::get();
}

void permission_manager_test() {
    cpptf::change_section("permission manager");
    tes::PermissionManager mng;
    std::string_view view;
    std::string text1("Hoge");
    view = mng.getSv(text1);
    text1.clear();
    cpptf::isSame("hold scope", view, "Hoge");
}

void moneyAddTrigger_test_prepare() {
    std::ofstream ofs("trigger_testdata.json");
    ofs <<
    R"({
        "SurfaceBlockBreak" : {
            "DirtBreak" : [
                [2,0],
                [3,0]
            ],
            "SandBreak" : [
                [12,0],
                [12,1]
            ]
        }
        })" << std::endl;
}
void moneyAddTrigger_test() {
    cpptf::change_section("MoneyAddTriggerManager");
    moneyAddTrigger_test_prepare();
    tes::MoneyAddTriggerManager mng;
    mng.load(std::ifstream("trigger_testdata.json"));
    auto trigger(mng.getTriggerOnBreak(12,0));
    cpptf::isTrue("get", trigger && *trigger.value() == "SandBreak");
    auto trigger2(mng.getTriggerOnBreak(99,0));
    cpptf::isFalse("get_unknown", trigger2);
}

void countryEconomy_test() {
    cpptf::change_section("CountryEconomy");
    auto country = tes::Country("Japan", 1);
    auto economy = tes::CountryEconomy(country);
    auto cur = std::make_shared<tes::Currency>(std::string("jpy"));
    economy.setCurrency(cur);
    cpptf::isSame("get currency", economy.getCurrency(), cur);
    std::shared_ptr<tes::PlayerMoney> money = std::make_shared<tes::PlayerMoney>(tes::PlayerIdentify());
    tes::MoneyAddTriggerKey trigger = std::make_shared<std::string>("trigger1");
    cpptf::isFalse("unknown_trigger", economy.existsTrigger(trigger));
    economy.updateTrigger(trigger,30);
    cpptf::isTrue("unknown_trigger", economy.existsTrigger(trigger));
    economy.runTrigger(trigger, money);
    cpptf::isTrue("add money", money->has(tes::Money(30,cur)));
}





int main() {
    tes::init_Database();
    tes::DataManager::get();
    tes::init_Database();
    permission_manager_test();
    Citizen_test();
    moneyAddTrigger_test();
    countryEconomy_test();
    dataLoad_test();
    cpptf::complete();
    return 0;
}
