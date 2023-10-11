#include <manager/CountryManager.hpp>
#include <fstream>
#include <filesystem>
namespace tes {

std::shared_ptr<Country> CountryManager::getCountry(CountryManager::country_id id) {
    return this->country.at(id);
}

void CountryManager::loadAll() {
    std::filesystem::create_directories(data_save_path);
    for (const auto& entry : std::filesystem::directory_iterator(data_save_path)) {
        if (!std::filesystem::is_regular_file(entry)) continue;
        nlohmann::json j = nlohmann::json::parse(std::ifstream(entry.path()));
        std::shared_ptr<tes::Country> add_country(new Country(j));
        this->addCountry(add_country);
    }
}

void CountryManager::saveAll() {
    for (const auto& i : country) {
        std::ofstream(std::format("{}/{}.json", data_save_path, i.second->id))
            << i.second->get_json()  << std::endl;
    }
}

std::shared_ptr<CountryManager> CountryManager::get() {
    if (!instance) {
        instance = std::make_shared<CountryManager>();
    }
    return instance;
}

void CountryManager::addCountry(const std::shared_ptr<Country>& country_) {
    country.insert({country_->id, country_});
}

std::shared_ptr<Country> CountryManager::addCountry(const std::string& name) {
    std::shared_ptr<Country> new_country = std::make_shared<Country>(name, country.size());
    this->addCountry(new_country);
    return new_country;
}
}
