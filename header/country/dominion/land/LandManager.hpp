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
class DominionManager;
class LandManager {
public:
    LandManager(const DominionManager&);

    [[nodiscard]]
    std::optional<std::reference_wrapper<const Land>> getLand(Land_id_t) const noexcept;

    void serve(const std::shared_ptr<ServeLandOrder>&);

    std::shared_ptr<ServeLandOrder> prepareServe(PlayerIdentify ,geometry::Area2D area);

    [[nodiscard]]
    std::size_t getNextId() const noexcept;


private:
    std::unordered_map<Land_id_t, Land> lands;
    std::shared_ptr<DominionManager> dominion_mng;
};

}
#endif //TES_HEADER_COUNTRY_DOMINION_LAND_LANDMANAGER_HPP_
