#include <country/dominion/land/Land.hpp>
#include <utility>
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

Land::Land(std::size_t id,
           PlayerIdentify owner,
           const std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>>& areas)
           : id(id), owner(std::move(owner)){
    for (const auto& i : areas) {
        std::shared_ptr<LandArea> new_land_area(new LandArea(i.second, id, *this));
        i.first->addLand(new_land_area);
        area.push_back(new_land_area);
    }
}

}
