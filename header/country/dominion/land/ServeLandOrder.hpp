#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_SERVELANDORDER_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_SERVELANDORDER_HPP_
#include <utility>
#include <vector>
#include <variant>
#include <util/geometry/geometry.hpp>
#include <util/player_identify/PlayerIdentify.hpp>
#include <country/dominion/land/DominionLand.hpp>
#include "country/dominion/DominionManager.hpp"

namespace tes {
class ServeLandOrder {
public:
    enum class ErrorCode {
        None,
        ContainDifferentCountry,
        ContainNotCountryDominion,
        ServedLand
    };

    static std::variant<std::shared_ptr<ServeLandOrder>, ErrorCode> build(const DominionManager&,
                                                                          PlayerIdentify owner,
                                                                          geometry::Area2D area);

    ErrorCode canServe() const noexcept;

    std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>> area;

    PlayerIdentify owner;

private:
    explicit ServeLandOrder(PlayerIdentify player) : owner(std::move(player)) {}
};
}

#endif //TES_HEADER_COUNTRY_DOMINION_LAND_SERVELANDORDER_HPP_
