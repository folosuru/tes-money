#pragma once
#ifndef TES_HEADER_COUNTRY_DOMINION_DOMINION_HPP_
#define TES_HEADER_COUNTRY_DOMINION_DOMINION_HPP_
#include <memory>
#include <vector>
#include "country/dominion/land/LandArea.hpp"
#include "DominionManager.hpp"
#include <country/dominion/land/DominionLand.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <util/geometry/geometry.hpp>
namespace tes {
class Country;
class DominionIndex;
class Dominion {
public:
    geometry::Area2D area;
    const std::shared_ptr<DominionLand> land;

    static constexpr geometry::Area2D indexToArea(DominionIndex);
    Dominion() = delete;
    Dominion(const std::shared_ptr<Country>&, std::size_t id, DominionIndex index);
    const std::weak_ptr<Country> country;

private:
    std::size_t id;
};

}

#endif //TES_HEADER_COUNTRY_DOMINION_DOMINION_HPP_
