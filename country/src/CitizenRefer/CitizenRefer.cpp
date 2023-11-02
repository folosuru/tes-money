#include <manager/CitizenRefer.hpp>
#include <citizen/Citizen.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
namespace tes {

std::shared_ptr<Citizen> CitizenRefer::get(Types::player_name_view name) {
    if (citizen.contains(name)) {
        return citizen[name];
    } else {
        return nullptr;
    }
}

void CitizenRefer::add(const std::shared_ptr<Citizen>& citizen_) {
    citizen[citizen_->name] = citizen_;
}

void CitizenRefer::loadCitizen(const std::shared_ptr<CountryManager>& country_manager,
                               const std::shared_ptr<PermissionManager>& perm_mng) {
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement query(db,
                            R"(SELECT citizen.name, permission, citizen.country
    FROM citizen LEFT OUTER JOIN citizen_permission ON citizen.name = citizen_permission.name
    ORDER BY citizen.name)");

    // 無駄にスコープ広げてる、ごめん
    // whileで初期化式が使えないのが悪い（暴論）
    std::unordered_set<Permission> permission_list;
    std::string last_name;
    std::shared_ptr<CitizenRefer> refer_(this);
    while (query.executeStep()) {
        std::string name = query.getColumn(0).getString();
        SQLite::Column permission = query.getColumn(1);
        int country = query.getColumn(2).getInt();
        if (name != last_name) {
            Citizen::build(refer_, country_manager->getCountry(country), last_name, permission_list);
            permission_list.clear();
            last_name = name;
        }
        if (permission.isNull()) {
            Citizen::build(refer_, country_manager->getCountry(country), name);
            continue;
        }
        permission_list.insert(perm_mng->getSv(permission.getString()));
    }
}

}
