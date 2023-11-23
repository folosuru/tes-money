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
      economy(CountryEconomy::load(id, trigger, currency)) {
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
    return std::make_shared<Country>(name,
                                     id_,
                                     std::make_shared<CountryCitizen>(),
                                     CountryEconomy::load(id_, trigger, currency));
}
}
