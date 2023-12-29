#pragma once
#ifndef TES_HEADER_COUNTRY_DOMINION_DOMINIONMANAGER_HPP_
#define TES_HEADER_COUNTRY_DOMINION_DOMINIONMANAGER_HPP_
#include <memory>
#include <optional>
#include <country/CountryManager.hpp>
#include <util/geometry/geometry.hpp>
#include "DominionIndex.hpp"
#include "country/dominion/range/DominionRange.hpp"

namespace tes {
class Dominion;
constexpr int convertIndex(int);
class DominionManager {
public:
    static constexpr int dominion_size = 100;

    static constexpr DominionIndex pos_to_index(geometry::Point2D point) {
        return {convertIndex(point.x), convertIndex(point.z)};
    }

    /**
     * get dominion
     * @param x
     * @param z
     * @return dominion
     */
    [[nodiscard]]
    std::optional<std::shared_ptr<Dominion>> get(DominionIndex) const noexcept;

    void serve(const std::shared_ptr<Country>&, DominionIndex);

    static std::shared_ptr<DominionManager> load(const std::shared_ptr<CountryManager> &mng);

    [[nodiscard]] std::size_t getNextId() const noexcept;

    [[nodiscard]]
    DominionRange getRange(DominionIndex start, DominionIndex end) const;


private:
    std::unordered_map<int,
        std::unordered_map<int, std::shared_ptr<Dominion>>> dominion;

    std::size_t dominion_count = 0;

    void add_without_WriteDB(int x,int z, const std::shared_ptr<Dominion>&);
};
constexpr int convertIndex(int value) {
    return (value < 0) ? (value / DominionManager::dominion_size) - 1 : value / DominionManager::dominion_size;
}
}
#endif //TES_HEADER_COUNTRY_DOMINION_DOMINIONMANAGER_HPP_
