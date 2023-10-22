#include "DataLoader.hpp"
namespace tes::Country_task {
std::string db_name = "country.sqlite";

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
