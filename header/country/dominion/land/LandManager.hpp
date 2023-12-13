#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
#include  <memory>
#include <functional>
#include "LandArea.hpp"
#include "ServeLandOrder.hpp"
#include <unordered_map>
#include <util/geometry/geometry.hpp>
#include <optional>
namespace tes {
using Land_id_t = int;
using land_ref = std::reference_wrapper<const Land>;
class DominionManager;
class LandManager {
public:
    LandManager(const DominionManager&);

    enum class LandFoundStatus {
        not_dominion,
        already_served
    };

    [[nodiscard]]
    static Arrai18n::trl_text getStatusText(const LandFoundStatus&) noexcept;

    [[nodiscard]]
    std::variant<land_ref, LandFoundStatus> getLand(const geometry::Point2D&) const noexcept;

    [[nodiscard]]
    std::optional<std::reference_wrapper<const Land>> getLand(Land_id_t) const noexcept;

    void serve(const std::shared_ptr<ServeLandOrder>&);

    std::variant<std::shared_ptr<ServeLandOrder>, LandFoundStatus> prepareServe(PlayerIdentify ,geometry::Area2D area);

    [[nodiscard]]
    std::size_t getNextId() const noexcept;


private:
    std::unordered_map<Land_id_t, Land> lands;
    std::shared_ptr<DominionManager> dominion_mng;
};

}
#endif //TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
