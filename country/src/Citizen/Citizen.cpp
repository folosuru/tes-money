#include <citizen/Citizen.hpp>
#include <stdexcept>
namespace tes {
bool Citizen::hasPermission(tes::Permission perm) {
    return this->permission.contains(perm);
}

Citizen::Citizen(std::shared_ptr<Country> country_,std::string name_) : country(country_), name(name_) {
    if (!country_) {
        throw std::invalid_argument("country cannot be nullptr");
    }
}
}