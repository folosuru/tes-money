#include <country/dominion/DominionManager.hpp>
#include <util/Resources.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <country/dominion/Dominion.hpp>
#include <AsyncTask/TaskManager.hpp>
#include "task/ServeDominionTask.hpp"

namespace tes {
std::optional<std::shared_ptr<Dominion>> DominionManager::get(DominionIndex index) const noexcept {
    if (auto x_find = dominion.find(index.x);
        x_find != dominion.end()) {
        if (auto z_find = x_find->second.find(index.z);
            z_find != x_find->second.end()) {
            return z_find->second;
        }
    }
    return std::nullopt;
}

std::shared_ptr<DominionManager> DominionManager::load(const std::shared_ptr<CountryManager>& mng) {
    std::shared_ptr<DominionManager> result = std::make_shared<DominionManager>();
    SQLite::Database db(getDominionDB());
    SQLite::Statement query(db, "SELECT x,z,country FROM dominion");
    while (query.executeStep()) {
        int x = query.getColumn(0);
        int z = query.getColumn(1);
        CountryManager::country_id id = query.getColumn(2);
        result->add_without_WriteDB(x, z, std::make_shared<Dominion>(mng->getCountry(id), result->getNextId(),
                                                                     pos_to_index({x,z})));
    }
    return result;
}

void DominionManager::serve(const std::shared_ptr<Country>& country, DominionIndex index) {
    dominion[index.x].insert({index.z, std::make_shared<Dominion>(country, dominion_count, index)});
    AsyncTask::add_task(std::make_shared<ServeDominionTask>(index.x, index.z, country->id, dominion_count));
    dominion_count++;
}

void DominionManager::add_without_WriteDB(int x, int z, const std::shared_ptr<Dominion>& dominion_) {
    dominion[x].insert({z, dominion_});
    dominion_count++;
}


std::size_t DominionManager::getNextId() const noexcept {
    return dominion_count;
}

DominionRange DominionManager::getRange(DominionIndex start,
                                        DominionIndex end) const {
    return DominionRange(*this,start, end);
}
}