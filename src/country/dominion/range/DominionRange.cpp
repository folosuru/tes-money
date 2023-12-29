#include <iostream>
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
    if (width == end.x) {
        width = start.x;
        height++;
    } else {
        width++;
    }
    return *this;
}

bool DominionRangeIter::operator==(const DominionRangeEnd& other) const {
    if (height > end.z) {
        return true;
    }
    return false;
}

bool DominionRangeIter::operator!=(const DominionRangeEnd& other) const {
    return !operator==(other);
}

std::optional<std::shared_ptr<Dominion>> DominionRangeIter::operator*() const {
    return mng.get({width,height});
}

DominionIndex getMin(const DominionIndex v1, const DominionIndex v2) {
    return DominionIndex{std::min(v1.x, v2.x), std::min(v1.z, v2.z)};
}
DominionIndex getMax(const DominionIndex v1, const DominionIndex v2) {
    return DominionIndex{std::max(v1.x, v2.x), std::max(v1.z, v2.z)};
}

DominionRangeIter::DominionRangeIter(const DominionManager& mng_, DominionIndex start, DominionIndex end)
 : mng(mng_), start(getMin(start, end)), end(getMax(start,end)), width(start.x), height(start.z){

}
}