#pragma once
#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_DOMINIONLAND_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_DOMINIONLAND_HPP_
#include <money/Money.hpp>
#include "LandArea.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/geometry/geometry.hpp>
#include <types/LandTypes.hpp>
namespace tes {
class DominionLand {
public:
    explicit DominionLand(geometry::Area2D);

    [[nodiscard]]
    std::optional<std::reference_wrapper<const Types::land_area>> getLand(int x, int y) const noexcept;

    [[nodiscard]]
    inline std::optional<Types::land_area_ref> getLand(const geometry::Point2D& point) const noexcept {
        return getLand(point.x, point.z);
    }

    [[nodiscard]] bool isServed(const geometry::Area2D&) const noexcept;

    void addLand(const std::shared_ptr<LandArea>&);

    const geometry::Area2D area;

    [[nodiscard]] const Money& getPrice() const noexcept {
        return Price;
    }
private:
    std::vector<std::shared_ptr<LandArea>> lands;

    // Per 1x1 area.
    Money Price;
};
}

#endif //TES_HEADER_COUNTRY_DOMINION_LAND_DOMINIONLAND_HPP_
