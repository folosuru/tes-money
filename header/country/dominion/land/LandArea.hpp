#pragma once
#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_LANDAREA_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_LANDAREA_HPP_
#include <util/player_identify/PlayerIdentify.hpp>
#include "util/geometry/geometry.hpp"

namespace tes {
class Land;
class LandManager;
class LandArea {
public:
    geometry::Area2D area;
    std::size_t id;

    LandArea() = delete;

    bool canAccess(const PlayerIdentify&);

    const Land& land;
private:
    LandArea(geometry::Area2D area, std::size_t id, const Land&);

    friend Land;
    friend LandManager;
};
}

#endif //TES_HEADER_COUNTRY_DOMINION_LAND_LANDAREA_HPP_
