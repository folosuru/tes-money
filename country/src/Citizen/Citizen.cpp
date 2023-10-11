#include <citizen/Citizen.hpp>
#include <stdexcept>
#include <utility>
#include <manager/CitizenRefer.hpp>
#include <country/Country.hpp>
namespace tes {
bool Citizen::hasPermission(tes::Permission perm) {
    return this->permission.contains(perm);
}

Citizen::Citizen(const std::shared_ptr<CitizenRefer>& refer,
                 const std::shared_ptr<Country>& country_,
                 std::string name_) : country(country_), name(std::move(name_)) {
    if (!country_) {
        throw std::invalid_argument("country cannot be nullptr");
    }
    refer->add(std::shared_ptr<Citizen>(this));
    country_->getCitizenManager()->add(name, std::shared_ptr<Citizen>(this));
}

void Citizen::addPermission(Permission perm) {
    if (!permission.contains(perm)) {
        permission.insert(perm);
    }
}

void Citizen::removePermission(Permission perm) {
    if (!permission.contains(perm)) {
        permission.erase(perm);
    }
}
}
