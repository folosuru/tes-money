#include <manager/CountryManager.hpp>
#include <fstream>
#include <filesystem>
#include <util/Resources.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
namespace tes {

std::shared_ptr<Country> CountryManager::getCountry(CountryManager::country_id id) const {
    return this->country.at(id);
}

void CountryManager::loadAll() {
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS country (name string, country int);");

    SQLite::Statement query(db, "SELECT name, country FROM country");
    while (query.executeStep()) {
        std::string name = query.getColumn(0).getString();
        int country_id = query.getColumn(1);
        this->addCountry(std::make_shared<Country>(name, country_id));
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
    std::shared_ptr<Country> new_country = std::make_shared<Country>(name, (country_id)country.size());
    this->addCountry(new_country);
    return new_country;
}
}
