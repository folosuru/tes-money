#include <manager/CitizenRefer.hpp>
#include <citizen/Citizen.hpp>
namespace tes {

std::shared_ptr<Citizen> CitizenRefer::get(Types::player_name_view name) {
    if (citizen.contains(name)) {
        return citizen[name];
    } else {
        return nullptr;
    }
}

void CitizenRefer::add(const std::shared_ptr<Citizen>& citizen_) {
    citizen[citizen_->name] = citizen_;
}
}
