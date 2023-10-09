#include <manager/CountryManager.hpp>
#include <fstream>
#include <filesystem>
#include <Nlohmann/json.hpp>
namespace tes {

std::shared_ptr<Country> CountryManager::get(CountryManager::country_id id) {
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

}