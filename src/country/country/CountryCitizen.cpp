#include <country/citizen/Countrycitizen.hpp>
#include "task/CitizenBanTask.hpp"
#include "task/CitizenJoinTask.hpp"
#include <AsyncTask/TaskManager.hpp>
#include <stdexcept>

namespace tes {
std::shared_ptr<Citizen> CountryCitizen::getCitizen(const PlayerIdentify& name) {
    if (citizens.contains(name)) {
        return citizens.at(name);
    } else {
        throw std::invalid_argument("citizen not found");
    }
}

void CountryCitizen::add(const std::shared_ptr<Citizen>& citizen_) {
    if (citizens.contains(citizen_->name)) {
        throw std::runtime_error("citizen already exists!");
    }
    AsyncTask::add_task(std::make_shared<CitizenJoinTask>(citizen_->name->name, citizen_->getCountry()->id));
    citizens.insert({citizen_->name, citizen_});
}

void CountryCitizen::ban(const PlayerIdentify& name) {
    if (!citizens.contains(name)) {
        throw std::runtime_error("Citizen not exists");
    }
    AsyncTask::add_task(std::make_shared<CitizenBanTask>(name->name));
    citizens.erase(name);
}

}
