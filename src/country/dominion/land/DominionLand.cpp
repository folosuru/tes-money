#include <country/dominion/land/DominionLand.hpp>
#include "task/NewLandTask.hpp"

namespace tes {
DominionLand::DominionLand(geometry::Area2D area) : area(area) {

}

std::optional<std::reference_wrapper<const Types::land_area>> DominionLand::getLand(int x, int z) const noexcept {
    for (const auto& i : lands) {
        if (i->area.contains(x, z)) {
            return std::cref(*i);
        }
    }
    return std::nullopt;
}

void DominionLand::addLand(const std::shared_ptr<LandArea>& new_land) {
    lands.push_back(new_land);
}

bool DominionLand::isServed(const geometry::Area2D& find_area) const noexcept {
    for (const auto& i : lands) {
        if (i->area.contains(find_area)) {
            return true;
        }
    }
    return false;
}
}