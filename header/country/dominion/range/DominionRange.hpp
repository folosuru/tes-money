#ifndef TES_HEADER_COUNTRY_DOMINION_RANGE_DOMINIONRANGE_HPP_
#define TES_HEADER_COUNTRY_DOMINION_RANGE_DOMINIONRANGE_HPP_
#include <country/dominion/DominionIndex.hpp>
#include <memory>
#include <optional>
namespace tes {
class Dominion;
class DominionManager;
class DominionIndex;

struct DominionRangeEnd {
    DominionRangeEnd() = default;
};

class DominionRangeIter {
public:
    DominionRangeIter& operator++();
    DominionRangeIter(const DominionManager&, DominionIndex start, DominionIndex end);
    bool operator!=(const DominionRangeEnd& other) const;
    bool operator==(const DominionRangeEnd& other) const;
    std::optional<std::shared_ptr<Dominion>> operator*() const;

private:
    DominionIndex start, end;
    int width = 0;
    int height = 0;
    const DominionManager& mng;
};

class DominionRange {
public:
    DominionRange(const DominionManager&, DominionIndex start, DominionIndex end);
    DominionRangeIter begin();
    DominionRangeEnd end();

private:
    const DominionManager& manager;
    DominionIndex start_point;
    DominionIndex end_point;
};
}

#endif //TES_HEADER_COUNTRY_DOMINION_RANGE_DOMINIONRANGE_HPP_
