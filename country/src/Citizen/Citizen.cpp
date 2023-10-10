#include <citizen/Citizen.hpp>
#include <stdexcept>
#include <utility>
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
}