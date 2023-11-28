#include <country/CountryManager.hpp>
#include <fstream>
#include <filesystem>
#include <util/Resources.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

namespace tes {

std::shared_ptr<Country> CountryManager::getCountry(CountryManager::country_id id) const {
    return this->country.at(id);
}

std::shared_ptr<CountryManager> CountryManager::build(const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                                                      const std::shared_ptr<CurrencyManager>& currency) {

    std::shared_ptr<CountryManager> result = std::make_shared<CountryManager>();
    SQLite::Database db(country_db_file,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec("CREATE TABLE IF NOT EXISTS country (name string, country int);");
    SQLite::Statement query(db, "SELECT name, country FROM country");
    while (query.executeStep()) {
        std::string name = query.getColumn(0).getString();
        int country_id = query.getColumn(1);
        result->addCountry(Country::load(name, country_id, trigger, currency));
    }
    return result;
}

void CountryManager::saveAll() {
    for (const auto& i : country) {
        std::ofstream(std::format("{}/{}.json", data_save_path, i.second->id))
            << i.second->get_json() << std::endl;
    }
}

void CountryManager::addCountry(const std::shared_ptr<Country>& country_) {
    country.insert({country_->id, country_});
}

const std::unordered_map<CountryManager::country_id,
                         std::shared_ptr<Country>>& CountryManager::getAll() const noexcept {
    return this->country;
}

CountryManager::country_id CountryManager::genNextCountryId() const noexcept {
    return this->country.size();
}

}
