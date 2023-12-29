#include <country/dominion/Dominion.hpp>
#include "country/dominion/land/LandManager.hpp"

namespace tes {


Dominion::Dominion(const std::shared_ptr<Country>& country, std::size_t id, DominionIndex index)
: country(country), id(id), land(std::make_shared<DominionLand>(DominionLand(indexToArea(index)))), area(indexToArea(index)) {

}
namespace {

}
constexpr geometry::Area2D Dominion::indexToArea(DominionIndex index) {
    return {
        {
            convertIndexToPosMax(index.x),
                           convertIndexToPosMax(index.z)
        },
        {
                            convertIndexToPosMin(index.x),
                            convertIndexToPosMin(index.z)
        }
    };
}
}