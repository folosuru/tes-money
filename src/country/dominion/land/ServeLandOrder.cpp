#include <country/dominion/land/ServeLandOrder.hpp>
#include <country/dominion/Dominion.hpp>
#include <utility>

namespace tes {

std::variant<std::shared_ptr<ServeLandOrder>,
             ServeLandOrder::ErrorCode> ServeLandOrder::build(const DominionManager& dominion,
                                                              PlayerIdentify owner,
                                                              geometry::Area2D area) {
    std::shared_ptr<ServeLandOrder> result(new ServeLandOrder(std::move(owner)));
    auto first_dominion = dominion.get(DominionManager::pos_to_index(area.getStartPos()));
    if (!first_dominion) {
        return {ServeLandOrder::ErrorCode::ContainNotCountryDominion};
    }
    auto target_range = dominion.getRange(DominionManager::pos_to_index(area.getStartPos()),
                                          DominionManager::pos_to_index(area.getEndPos()));
    for (const auto& i : target_range) {
        if (!i) {
            return {ServeLandOrder::ErrorCode::ContainNotCountryDominion};
        }
        if (i.value()->country.lock() != first_dominion.value()->country.lock()) {
            return {ServeLandOrder::ErrorCode::ContainDifferentCountry};
        }
        geometry::Area2D serve_area{{std::max(i.value()->area.min_x, area.min_x),
                          std::max(i.value()->area.min_z, area.min_z)},
                         {std::min(i.value()->area.max_x, area.max_x),
                          std::max(i.value()->area.max_z, area.max_z)}};
        if (i.value()->land->isServed(serve_area)) {
            return {ServeLandOrder::ErrorCode::ServedLand};
        }
        result->area.push_back({i.value()->land, serve_area});
    }
    return result;
}

ServeLandOrder::ErrorCode ServeLandOrder::canServe() const noexcept {
    for (const auto& i : area) {
        if (i.first->isServed(i.second)) {
            return ErrorCode::ServedLand;
        }
    }
    return ServeLandOrder::ErrorCode::None;
}
}