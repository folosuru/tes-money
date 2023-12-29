#include <iostream>
#include <country/dominion/land/ServeLandOrder.hpp>
#include <country/dominion/Dominion.hpp>
#include <utility>

namespace tes {
std::variant<std::shared_ptr<ServeLandOrder>,
             ServeLandOrder::ErrorCode> ServeLandOrder::build(const DominionManager& dominion,
                                                              PlayerIdentify owner,
                                                              const geometry::Area2D area) {
    auto first_dominion = dominion.get(DominionManager::pos_to_index(area.getStartPos()));
    if (!first_dominion) {
        return {ServeLandOrder::ErrorCode::ContainNotCountryDominion};
    }
    auto target_range = dominion.getRange(DominionManager::pos_to_index(area.getStartPos()),
                                          DominionManager::pos_to_index(area.getEndPos()));
    std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>> area_list;

    for (const auto& i : target_range) {
        if (!i) {
            return {ServeLandOrder::ErrorCode::ContainNotCountryDominion};
        }
        if (i.value()->country.lock() != first_dominion.value()->country.lock()) {
            return {ServeLandOrder::ErrorCode::ContainDifferentCountry};
        }
        geometry::Area2D serve_area {area.getDuplicateArea(i.value()->area)};

        if (i.value()->land->isServed(serve_area)) {
            return {ServeLandOrder::ErrorCode::ServedLand};
        }
        area_list.emplace_back(i.value()->land, serve_area);
        ;
    }
    return std::shared_ptr<ServeLandOrder>(new ServeLandOrder(std::move(owner), area_list, area));
}

ServeLandOrder::ErrorCode ServeLandOrder::canServe() const noexcept {
    for (const auto& [land_mng, area] : separate_area) {
        if (land_mng->isServed(area)) {
            return ErrorCode::ServedLand;
        }
    }
    return ServeLandOrder::ErrorCode::None;
}

ServeLandOrder::ServeLandOrder(PlayerIdentify player,
                               std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>> separate_area_,
                               const geometry::Area2D& area)
    : area(area), owner(std::move(player)), separate_area(std::move(separate_area_)),
      Price([](const std::vector<std::pair<std::shared_ptr<DominionLand>, geometry::Area2D>>& lands) {
          Money result;
          for (const auto& i : lands) {
              result = result + i.first->getPrice() * i.second.getAreaSize();
          }
          return result;
      }(separate_area)) {}
}
