#include <manager/CountryManager.hpp>

namespace tes {

std::shared_ptr<Country> CountryManager::get(CountryManager::country_id id) {
    return this->country.at(id);
}


}