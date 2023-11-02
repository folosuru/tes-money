#include <util/Resources.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

namespace tes {
void init_Database() {
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS citizen (name string, country int);");
    db.exec("CREATE TABLE IF NOT EXISTS citizen_permission (name string, permission text, unique(name,permission));");
}
}