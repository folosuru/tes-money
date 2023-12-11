#pragma once
#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_DOMINIONLAND_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_DOMINIONLAND_HPP_
#include "LandArea.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/geometry/geometry.hpp>
namespace tes {
using land_type = LandArea;
class DominionLand {
public:
    explicit DominionLand(geometry::Area2D);

    [[nodiscard]]
    std::optional<std::reference_wrapper<const land_type>> getLand(int x, int y) const noexcept;

    [[nodiscard]]
    inline std::optional<std::reference_wrapper<const land_type>> getLand(const geometry::Point2D& point) const noexcept {
        return getLand(point.x, point.z);
    }

    [[nodiscard]] bool isServed(const geometry::Area2D&) const noexcept;

    void addLand(const std::shared_ptr<LandArea>&);

    const geometry::Area2D area;
private:
    std::vector<std::shared_ptr<LandArea>> lands;
};
}

#endif //TES_HEADER_COUNTRY_DOMINION_LAND_DOMINIONLAND_HPP_
