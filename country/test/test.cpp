#include <iostream>
#include <stdexcept>
#include <fstream>
#include <country/Country.hpp>
#include <manager/CountryManager.hpp>
#include <manager/CitizenRefer.hpp>
#include <citizen/Citizen.hpp>
#include <permission/PermissionManager.hpp>
#include <cpptf/Cpptf.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

void Citizen_test() {
    using namespace tes;
    cpptf::change_section("Citizen");
    std::shared_ptr<CitizenRefer> refer = std::make_shared<CitizenRefer>();
    std::shared_ptr<Country> country = std::make_shared<Country>("Japan",1);
    std::string_view perm = "foo";
    auto citizen_ = Citizen(refer, country, "taro");
    cpptf::isFalse("permission not found", citizen_.hasPermission(perm));
    citizen_.addPermission(perm);
    cpptf::isTrue("permission found", citizen_.hasPermission(perm));
    citizen_.removePermission(perm);
    cpptf::isTrue("permission remove", citizen_.hasPermission(perm));
}

void load_citizen() {
    using namespace tes;
    cpptf::change_section("Citizen");
    std::shared_ptr<CitizenRefer> refer = std::make_shared<CitizenRefer>();
    std::shared_ptr<Country> country = std::make_shared<Country>("Japan",1);

}

void permission_manager_test() {
    cpptf::change_section("permission manager");
    tes::PermissionManager mng;
    std::string_view view;
    {
        std::string text1("Hoge");
        view = mng.getSv(text1);
    }
    cpptf::isSame("hold scope",view,"Hoge");
}

void sql_t() {
    try
    {
        SQLite::Database    db("transaction.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        db.exec("DROP TABLE IF EXISTS test");

        // Begin transaction
        SQLite::Transaction transaction(db);

        db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

        int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
        std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

        // Commit transaction
        transaction.commit();
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}


int main() {
    permission_manager_test();
    sql_t();
    Citizen_test();
    cpptf::complete();
    return 0;
}
