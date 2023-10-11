#include <iostream>
#include <stdexcept>
#include <fstream>
#include <country/Country.hpp>
#include <manager/CountryManager.hpp>
#include <manager/CitizenRefer.hpp>
#include <citizen/Citizen.hpp>
#include <Cpptf.hpp>

void Citizen_test() {
    using namespace tes;
    cpptf::change_section("Citizen");
    std::shared_ptr<CitizenRefer> refer = std::make_shared<CitizenRefer>();
    std::shared_ptr<Country> country = std::make_shared<Country>("Japan",1);
    auto citizen_ = Citizen(refer, country, "taro");
    cpptf::isFalse("permission not found", citizen_.hasPermission(Permission::money));
    citizen_.addPermission(Permission::money);
    cpptf::isTrue("permission found", citizen_.hasPermission(Permission::money));
    citizen_.removePermission(Permission::money);
    cpptf::isTrue("permission remove", citizen_.hasPermission(Permission::money));
}

int main() {
    Citizen_test();
    cpptf::complete();
    return 0;
}
