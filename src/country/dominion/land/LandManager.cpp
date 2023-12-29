#include <country/dominion/land/LandManager.hpp>
#include <algorithm>
#include <iostream>
#include <AsyncTask/TaskManager.hpp>
#include <country/dominion/DominionManager.hpp>
#include <country/dominion/land/Land.hpp>
#include <utility>
#include <country/dominion/Dominion.hpp>
#include <util/Resources.hpp>
#include <types/LandTypes.hpp>
#include "task/NewLandTask.hpp"

namespace tes {
Types::Land_id_t LandManager::serve(const std::shared_ptr<ServeLandOrder>& order) {
    Types::Land_id_t id = getNextId();
    lands.insert({id, std::make_unique<Land>(id, order->owner, order->separate_area)});
    AsyncTask:add_task(std::make_shared<NewLandTask>(order, id));
    return id;
}

std::variant<std::shared_ptr<ServeLandOrder>, ServeLandOrder::ErrorCode> LandManager::prepareServe(PlayerIdentify owner,
    geometry::Area2D area) {
    return ServeLandOrder::build(dominion_mng, std::move(owner), area);
}

std::variant<Types::land_area_ref, LandManager::LandFoundStatus> LandManager::getLandByPos(const geometry::Point2D& point) const {
    if (auto dominion = this->dominion_mng.get(DominionManager::pos_to_index(point));
        dominion.has_value()) {
        if (auto land = dominion.value()->land->getLand(point);
            land.has_value()) {
            return land.value();
        }
        return LandFoundStatus::not_served;
    }
    return LandFoundStatus::not_dominion;
}

Types::Land_id_t LandManager::getNextId() const noexcept {
    return lands.size();
}

void LandManager::loadFromDB(const std::shared_ptr<PlayerIdentifyProvider>& provider) {
    SQLite::Database db(getDominionDB());
    SQLite::Statement getLandsQuery(db, "SELECT owner, id FROM  land_owner;");
    while (getLandsQuery.executeStep()) {
        std::string owner{getLandsQuery.getColumn(0)};
        Types::Land_id_t id{getLandsQuery.getColumn(1)};
        lands.insert({id, Land::load(id, provider->getIdentify(owner), dominion_mng, provider)});
    }
}

std::shared_ptr<LandManager> LandManager::load(const DominionManager& dominion_manager, std::shared_ptr<PlayerIdentifyProvider> identify) {
    auto result = std::make_shared<LandManager>(dominion_manager);
    result->loadFromDB(identify);
    return result;
}

LandManager::LandManager(const DominionManager& dominion)  : dominion_mng(dominion){
}

Arrai18n::trl_text LandManager::getStatusText(const LandFoundStatus& status) noexcept {
    switch (status) {
        case LandFoundStatus::already_served: {
            return {"land.found_status.already_served"};
        }
        case LandFoundStatus::not_dominion: {
            return {"land.found_status.not_dominion"};
        }
        case LandFoundStatus::not_served: {
            return {"land.found_status.not_served"};
        }
        default: {
            return {"unknown status value at getStatusText"};
        }
    }
}

std::optional<std::reference_wrapper<const Land>> LandManager::getLand(Types::Land_id_t id) const noexcept {
    return std::ref(*lands.at(id));
}

}
