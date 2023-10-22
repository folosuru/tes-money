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
    country_->getCitizenManager()->add(std::shared_ptr<Citizen>(this));
}

Citizen::Citizen(const std::shared_ptr<CitizenRefer>& refer_,
                 const std::shared_ptr<Country>& country_,
                 std::string name_,
                 std::unordered_set<Permission> permission_)
                 : Citizen(refer_, country_, std::move(name_)) {
    permission = std::move(permission_);
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

const std::shared_ptr<Country>& Citizen::GetCountry() const {
    return country;
}

const std::unordered_set<Permission>& Citizen::getAllPermission() const noexcept {
    return permission;
}


}
