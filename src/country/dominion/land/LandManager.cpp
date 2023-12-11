#include <country/dominion/land/LandManager.hpp>
#include <algorithm>
#include <country/dominion/DominionManager.hpp>
#include <country/dominion/land/Land.hpp>
namespace tes {

void LandManager::serve(const std::shared_ptr<ServeLandOrder>& order) {
    std::size_t id = getNextId();
    lands.insert({id,Land(id, order->owner, order->area)});
}

std::size_t LandManager::getNextId() const noexcept {
    return lands.size();
}

std::optional<std::reference_wrapper<const Land>> LandManager::getLand(Land_id_t id) const noexcept {
    return std::ref(lands.at(id));
}

}