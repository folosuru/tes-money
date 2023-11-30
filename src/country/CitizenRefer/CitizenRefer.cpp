#include <country/citizen/CitizenRefer.hpp>
#include <country/citizen/Citizen.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/Resources.hpp>
#include <utility>

namespace tes {
std::shared_ptr<Citizen> CitizenRefer::get(Types::player_name_view name) {
    return this->get(this->identify_provider->getIdentify(name));
}

std::shared_ptr<Citizen> CitizenRefer::get(const PlayerIdentify& name) {
    if (auto result = citizen.find(name); result != citizen.end()) {
        return result->second;
    } else {
        return nullptr;
    }
}

void CitizenRefer::add(const std::shared_ptr<Citizen>& citizen_) {
    citizen[citizen_->name] = citizen_;
}

std::shared_ptr<CitizenRefer> CitizenRefer::load(const std::shared_ptr<CountryManager>& country_manager,
                                                 const std::shared_ptr<PermissionManager>& perm_mng,
                                                 const std::shared_ptr<PlayerIdentifyProvider>& identify) {
    SQLite::Database db(getCountryDB());
    SQLite::Statement query(db,
                            R"(SELECT citizen.name, permission, citizen.country
    FROM citizen LEFT OUTER JOIN citizen_permission ON citizen.name = citizen_permission.name
    ORDER BY citizen.name)");
    std::shared_ptr<CitizenRefer> refer_ = std::make_shared<CitizenRefer>(identify);
    // 無駄にスコープ広げてる、ごめん
    // whileで初期化式が使えないのが悪い（暴論）
    std::unordered_set<Permission> permission_list;
    std::string last_name;
    while (query.executeStep()) {
        std::string name = query.getColumn(0).getString();
        SQLite::Column permission = query.getColumn(1);
        int country = query.getColumn(2).getInt();
        if (name != last_name) {
            if (!last_name.empty()) {
                Citizen::buildFromLoad(refer_,
                                       country_manager->getCountry(country),
                                       identify->getIdentify(last_name),
                                       permission_list);
            }
            permission_list.clear();
            last_name = name;
        }
        if (permission.isNull()) {
            Citizen::buildFromLoad(refer_,
                                   country_manager->getCountry(country),
                                   identify->getIdentify(name),
                                   std::unordered_set<Permission>());
            continue;
        }
        permission_list.insert(perm_mng->getSv(permission.getString()));
    }
    return refer_;
}

CitizenRefer::CitizenRefer(std::shared_ptr<PlayerIdentifyProvider> identify)
    : identify_provider(std::move(identify)) {}

void CitizenRefer::remove(const PlayerIdentify& identify) {
    citizen.erase(identify);
}

}
