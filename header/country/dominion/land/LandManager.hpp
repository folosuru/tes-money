#ifndef TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
#define TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
#include <memory>
#include <functional>
#include "LandArea.hpp"
#include "ServeLandOrder.hpp"
#include <unordered_map>
#include <variant>
#include <util/geometry/geometry.hpp>
#include <country/dominion/land/Land.hpp>
#include <types/LandTypes.hpp>
#include <optional>
namespace tes {
using land_ref = std::reference_wrapper<const Land>;
class DominionManager;
class LandManager {
public:
    explicit LandManager(const DominionManager&);

    enum class LandFoundStatus {
        not_dominion,
        already_served,
        not_served
    };

    [[nodiscard]]
    static Arrai18n::trl_text getStatusText(const LandFoundStatus&) noexcept;

    [[nodiscard]]
    std::optional<std::reference_wrapper<const Land>> getLand(Types::Land_id_t) const noexcept;

    Types::Land_id_t serve(const std::shared_ptr<ServeLandOrder>&);

    std::variant<std::shared_ptr<ServeLandOrder>, ServeLandOrder::ErrorCode> prepareServe(PlayerIdentify ,geometry::Area2D area);

    std::variant<Types::land_area_ref, LandFoundStatus> getLandByPos(const geometry::Point2D&) const;

    [[nodiscard]]
    Types::Land_id_t getNextId() const noexcept;

    void loadFromDB(const std::shared_ptr<PlayerIdentifyProvider>&);

    static std::shared_ptr<LandManager> load(const DominionManager&, std::shared_ptr<PlayerIdentifyProvider>);

private:
    std::unordered_map<Types::Land_id_t, std::unique_ptr<Land>> lands;
    const DominionManager& dominion_mng;
};

}
#endif //TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
