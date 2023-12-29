#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_SERVELANDORDER_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_SERVELANDORDER_HPP_
#include <utility>
#include <vector>
#include <variant>
#include <util/geometry/geometry.hpp>
#include <util/player_identify/PlayerIdentify.hpp>
#include <country/dominion/land/DominionLand.hpp>
#include "country/dominion/DominionManager.hpp"
#include <CppArrai18n/Arrai18n_def.hpp>

namespace tes {
class ServeLandOrder {
public:
    enum class ErrorCode {
        None,
        ContainDifferentCountry,
        ContainNotCountryDominion,
        ServedLand
    };
    static Arrai18n::trl_text errorCodeToText(ErrorCode) noexcept;

    static std::variant<std::shared_ptr<ServeLandOrder>, ErrorCode> build(const DominionManager&,
                                                                          PlayerIdentify owner,
                                                                          geometry::Area2D area);

    [[nodiscard]] ErrorCode canServe() const noexcept;


    const geometry::Area2D area;
    const PlayerIdentify owner;
    const std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>> separate_area;
    const Money Price;
private:
    explicit ServeLandOrder(PlayerIdentify player,
                            std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>>,
                            const geometry::Area2D& area);


};
}

#endif //TES_HEADER_COUNTRY_DOMINION_LAND_SERVELANDORDER_HPP_
