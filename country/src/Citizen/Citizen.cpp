#include <citizen/Citizen.hpp>
#include <stdexcept>
#include <utility>
#include <manager/CitizenRefer.hpp>
#include <AsyncTask/TaskManager.hpp>
#include "task/AddPermissionTask.hpp"
#include "task/RemovePermissionTask.hpp"
namespace tes {
bool Citizen::hasPermission(tes::Permission perm) {
    return this->permission.contains(perm);
}

Citizen::Citizen(const std::shared_ptr<Country>& country_,std::string name_)
    : country(country_), name(std::move(name_)) {
    if (country.lock()) {
        throw std::invalid_argument("country cannot be nullptr");
    }
}

Citizen::Citizen(const std::shared_ptr<Country>& country_,
                 std::string name_,
                 std::unordered_set<Permission> permission_)
                 : Citizen(country_, std::move(name_)) {
    permission = std::move(permission_);
}
void Citizen::addPermission(Permission perm) {
    if (!permission.contains(perm)) {
        permission.insert(perm);
        AsyncTask::add_task(std::make_shared<AddPermissionTask>(name, perm));
    }
}

void Citizen::removePermission(Permission perm) {
    if (permission.contains(perm)) {
        permission.erase(perm);
        AsyncTask::add_task(std::make_shared<RemovePermissionTask>(name, perm));
    }
}

std::shared_ptr<Country> Citizen::getCountry() const {
    return country.lock();
}

const std::unordered_set<Permission>& Citizen::getAllPermission() const noexcept {
    return permission;
}

std::shared_ptr<Citizen> Citizen::build(const std::shared_ptr<CitizenRefer>& refer,
                                        const std::shared_ptr<Country>& country_,
                                        std::string name,
                                        std::unordered_set<Permission> permission_) {
    std::shared_ptr<Citizen> ptr(new Citizen(country_,
                                             std::move(name),
                                             std::move(permission_)));
    refer->add(ptr);
    country_->getCitizenManager()->add(ptr);
    return ptr;
}
std::shared_ptr<Citizen> Citizen::build(const std::shared_ptr<CitizenRefer>& refer,
                                        const std::shared_ptr<Country>& country_,
                                        std::string name) {
    std::shared_ptr<Citizen> ptr(new Citizen(country_, std::move(name)));
    refer->add(ptr);
    country_->getCitizenManager()->add(ptr);
    return ptr;
}

}
