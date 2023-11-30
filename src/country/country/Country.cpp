#include <country/Country.hpp>
#include <memory>
#include <utility>

namespace tes {
Country::Country(std::string name_,
                 country_id id_,
                 std::shared_ptr<CountryCitizen> citizen_,
                 std::shared_ptr<CountryEconomy> economy_)
    : name(std::move(name_)),
      citizen(std::move(citizen_)),
      id(id_),
      economy(std::move(economy_)) {

}

Country::Country(std::string name_, Country::country_id id_)
    : name(std::move(name_)), id(id_), citizen(std::make_shared<CountryCitizen>()),
      economy(std::make_shared<CountryEconomy>(*this)) {}

nlohmann::json Country::get_json() {
    nlohmann::json result;
    result["id"] = id;
    result["name"] = name;
    return result;
}

Country::Country(nlohmann::json data,
                 const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                 const std::shared_ptr<CurrencyManager>& currency)
    : id(data["id"].get<country_id>()),
      name(data["name"].get<std::string>()),
      economy(CountryEconomy::load(*this, trigger, currency)) {
}

const std::string& Country::getName() {
    return name;
}

const std::shared_ptr<CountryEconomy>& Country::getEconomyManager() const noexcept {
    return economy;
}

std::shared_ptr<Country> Country::load(const std::string& name,
                                       Country::country_id id_,
                                       const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                                       const std::shared_ptr<CurrencyManager>& currency) {
    return std::shared_ptr<Country>(new Country(name, id_, trigger, currency));
}

Country::Country(std::string name_,
                 Country::country_id id_,
                 const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                 const std::shared_ptr<CurrencyManager>& currency)
    : name(std::move(name_)),
      citizen(std::make_shared<CountryCitizen>()),
      id(id_),
      economy(CountryEconomy::load(*this, trigger, currency)) {

}

}
