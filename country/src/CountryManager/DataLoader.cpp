//
// Created by folosuru on 2023/10/14.
//

#include "DataLoader.hpp"
namespace tes::Country_task {
std::string db_name = "country.sqlite";
void loadCitizen(std::shared_ptr<CountryManager> country_manager,
                 std::shared_ptr<CitizenRefer> refer_,
                 std::shared_ptr<PermissionManager> permission_mng) {
    SQLite::Database db(db_name,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS citizen (name string, country int);");
    db.exec("CREATE TABLE IF NOT EXISTS citizen_permission (name string, permission text);");

    SQLite::Statement query(db,
    R"(SELECT citizen.name, permission, citizen.country
    FROM citizen LEFT OUTER JOIN citizen_permission ON citizen.name = citizen_permission.name
    ORDER BY citizen.name)");

    // 無駄にスコープ広げてる、ごめん
    // whileで初期化式が使えないのが悪い（暴論）
    std::unordered_set<Permission> permission_list;
    std::string last_name;
    while (query.executeStep()) {
        std::string name = query.getColumn(0).getString();
        SQLite::Column permission = query.getColumn(1);
        int country = query.getColumn(2).getInt();
        if (name != last_name) {
            Citizen(refer_, country_manager->getCountry(country), last_name, permission_list);
            permission_list.clear();
            last_name = name;
        }
        if (permission.isNull()) {
            Citizen(refer_, country_manager->getCountry(country), name);
            continue;
        }
        permission_list.insert(permission.getString());
    }
}

void loadCountry(std::shared_ptr<CountryManager> manager ) {
    SQLite::Database db(db_name,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS country (name string, country int);");

    SQLite::Statement query(db, "SELECT name, country FROM country");
    while (query.executeStep()) {
        std::string name = query.getColumn(0).getString();
        int country_id = query.getColumn(1);
        manager->addCountry(std::make_shared<Country>(name, country_id));
    }
}

void saveCitizen(std::shared_ptr<Citizen> citizen) {
    SQLite::Database db("country.sqlite",
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement query(db, "DELETE from citizen_permission where name = ?");
    query.bind(1,citizen->name);
    query.exec();

}

}
