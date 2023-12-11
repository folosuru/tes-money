#include <country/dominion/land/LandArea.hpp>
#include <country/dominion/land/Land.hpp>
#include <country/dominion/land/LandManager.hpp>

namespace tes {

bool LandArea::canAccess(const PlayerIdentify& pl) {
    return (land.is_owner(pl) || land.is_shared(pl));
}

LandArea::LandArea(geometry::Area2D area, std::size_t id, const Land& land)
 : id(id), land(land), area(area){
}

}