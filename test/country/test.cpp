#include <stdexcept>
#include <fstream>
#include <country/Country.hpp>
#include <country/CountryManager.hpp>
#include <country/citizen/CitizenRefer.hpp>
#include <country/citizen/Citizen.hpp>
#include <misc/PermissionManager.hpp>
#include <cpptf/Cpptf.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
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

void permission_manager_test() {
    cpptf::change_section("permission manager");
    tes::PermissionManager mng;
    std::string_view view;
    std::string text1("Hoge");
    view = mng.getSv(text1);
    text1.clear();
    cpptf::isSame("hold scope", view, "Hoge");
}

int main() {
    tes::init_Database();
    permission_manager_test();
    Citizen_test();
    cpptf::complete();
    return 0;
}
