#include <util/Resources.hpp>
#include <filesystem>

namespace tes {
void init_Database() {
    std::filesystem::create_directories(resource::country_data_directory);
    SQLite::Database db(country_db_file, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS citizen (name string, country int);");
    db.exec("CREATE TABLE IF NOT EXISTS citizen_permission (name string, permission text, unique(name,permission));");
    db.exec("CREATE TABLE IF NOT EXISTS country (id int, name text, description text, currency text, unique(id));");
    db.exec(
        "CREATE TABLE IF NOT EXISTS country_money_trigger (trigger text, add_value int, country int, unique(country,trigger));");
}

SQLite::Database getCountryDB() {
    return SQLite::Database{country_db_file, SQLite::OPEN_READWRITE};
}

void reset_Database() {
    SQLite::Database db(getCountryDB());
    db.exec("drop table citizen");
    db.exec("drop table citizen_permission");
    db.exec("drop table country");
    db.exec("drop table country_money_trigger");
}

}