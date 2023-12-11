#include <country/dominion/Dominion.hpp>
#include "country/dominion/land/LandManager.hpp"

namespace tes {


Dominion::Dominion(const std::shared_ptr<Country>& country, std::size_t id, DominionIndex index)
: country(country), id(id), land(std::make_shared<DominionLand>(DominionLand(indexToArea(index)))), area(indexToArea(index)) {

}
namespace {
template<class T>
constexpr T convertIndexToPosAbsMax(T value) {
    return (value < 0) ? (value * DominionManager::dominion_size) +1  :
                         (value * DominionManager::dominion_size) -1;

}
template<class T>
constexpr T convertIndexToPosAbsMin(T value) {
    return (value < 0) ? ((value+1) * DominionManager::dominion_size)-1 :
                         ((value-1) * DominionManager::dominion_size);
}
}
constexpr geometry::Area2D Dominion::indexToArea(DominionIndex index) {
    return {convertIndexToPosAbsMax(index.x),
                            convertIndexToPosAbsMax(index.z),
                            convertIndexToPosAbsMin(index.x),
                            convertIndexToPosAbsMin(index.z)};
}
}