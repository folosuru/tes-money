#include <iostream>
#include <country/dominion/land/Land.hpp>
#include <memory>
#include <utility>
#include <country/dominion/Dominion.hpp>
#include <util/task/SQLiteExecTask.hpp>
namespace tes {
bool tes::Land::is_owner(const PlayerIdentify& target) const noexcept {
    return (owner== target);
}

bool Land::is_shared(const PlayerIdentify& target) const noexcept {
    return share_user.contains(target);
}

void Land::addShared(const PlayerIdentify& pl) {
    share_user.insert(pl);
}

std::unique_ptr<Land> Land::load(Types::Land_id_t id, PlayerIdentify owner, const DominionManager& dominion,
    std::shared_ptr<PlayerIdentifyProvider> identify) {
    SQLite::Database db(getDominionDB());
    SQLite::Statement getShareQuery(db, "SELECT share from land_share where id = ?");
    getShareQuery.bind(1, id);
    std::unordered_set<PlayerIdentify> share;
    std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>> lands;
    while (getShareQuery.executeStep()) {
        share.insert(identify->getIdentify(getShareQuery.getColumn(0)));
    }
    SQLite::Statement getAreaQuery(db, "SELECT x1, x2, z1, z2 FROM land_area where id = ?");
    getAreaQuery.bind(1, id);
    while (getAreaQuery.executeStep()) {
        geometry::Point2D p1{getAreaQuery.getColumn(0), getAreaQuery.getColumn(2)};
        geometry::Point2D p2{getAreaQuery.getColumn(1), getAreaQuery.getColumn(3)};
        lands.emplace_back(dominion.get(DominionManager::pos_to_index(p1)).value()->land, geometry::Area2D(p1,p2));
    }
    return std::make_unique<Land>(id, std::move(owner), lands, std::move(share));
}

Land::Land(std::size_t id,
           PlayerIdentify owner,
           const std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>>& areas,
           std::unordered_set<PlayerIdentify> share)
           : owner(std::move(owner)), id(id), share_user(std::move(share_user)){
    for (const auto& [dominion_, target_area] : areas) {
        std::shared_ptr<LandArea> new_land_area(new LandArea(target_area, id, *this));
        dominion_->addLand(new_land_area);
        area.push_back(new_land_area);
    }
}

}
