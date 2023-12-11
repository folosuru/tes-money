#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_LAND_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_LAND_HPP_
#include <util/player_identify/PlayerIdentify.hpp>
#include <country/dominion/land/LandArea.hpp>
#include <unordered_set>
#include "DominionLand.hpp"

namespace tes {
class Land {
public:
    const PlayerIdentify owner;

    std::size_t id;

    Land(std::size_t id, PlayerIdentify owner, geometry::Area2D area);

    Land(std::size_t id, PlayerIdentify owner, const std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>>&);

    [[nodiscard]] bool is_owner(const PlayerIdentify&) const noexcept;

    [[nodiscard]] bool is_shared(const PlayerIdentify&) const noexcept;

    [[nodiscard]] bool canUse(const PlayerIdentify& pl) const noexcept {
        return (is_owner(pl) || is_shared(pl));
    }

    void addShared(const PlayerIdentify&);

private:
    std::unordered_set<PlayerIdentify> share_user;

    std::vector<std::shared_ptr<LandArea>> area;
};
}

#endif //TES_HEADER_COUNTRY_DOMINION_LAND_LAND_HPP_
