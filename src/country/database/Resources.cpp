#include <util/Resources.hpp>

namespace tes {
void init_Database() {
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS citizen (name string, country int);");
    db.exec("CREATE TABLE IF NOT EXISTS citizen_permission (name string, permission text, unique(name,permission));");
    db.exec("CREATE TABLE IF NOT EXISTS country (id int, name text, description text, currency text, unique(id));");
    db.exec("CREATE TABLE IF NOT EXISTS country_money_trigger (trigger text, add_value int, country int, unique(country,trigger));");
}

SQLite::Database getCountryDB() {
    return SQLite::Database{country_db_file, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE};
}

}