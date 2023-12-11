#include <country/dominion/range/DominionRange.hpp>
#include <country/dominion/DominionManager.hpp>

namespace tes {

DominionRange::DominionRange(const DominionManager& mng, DominionIndex start, DominionIndex end)
 : manager(mng), start_point(start), end_point(end){

}

DominionRangeIter DominionRange::begin() {
    return DominionRangeIter(manager, start_point, end_point);
}

DominionRangeEnd DominionRange::end() {
    return DominionRangeEnd();
}

DominionRangeIter& DominionRangeIter::operator++() {
    width++;
    if (width + std::min(start.x, end.x) == 0) {
        width++;
    }
    if (width > std::max(start.x, end.x) - std::min(start.x, end.x)) {
        width = 0;
        height++;
        if (std::min(start.z, end.z) + height) {
            height++;
        }
    }
    return *this;
}

bool DominionRangeIter::operator==(const DominionRangeEnd& other) const {
    if (height > std::max(start.z, end.z) - std::min(start.z, end.z)) {
        return true;
    }
    return false;
}

bool DominionRangeIter::operator!=(const DominionRangeEnd& other) const {
    if (height > std::max(start.z, end.z) - std::min(start.z, end.z)) {
        return false;
    }
    return true;
}

std::optional<std::shared_ptr<Dominion>> DominionRangeIter::operator*() const {
    return mng.get({std::min(start.x, end.x) + width, std::min(start.z, end.z) + height});
}

DominionRangeIter::DominionRangeIter(const DominionManager& mng_, DominionIndex start, DominionIndex end)
 : mng(mng_), start(start), end(end){

}
}