#include <country/Country.hpp>
#include <memory>
namespace tes {
Country::Country(std::string name_,
                 country_id id_,
                 const std::shared_ptr<MoneyAddTriggerManager>& trigger,
                 const std::shared_ptr<CurrencyManager>& currency)
    : name(std::move(name_)),
      citizen(std::make_shared<CountryCitizen>()),
      id(id_),
      economy(CountryEconomy::load(id,trigger, currency) {

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
    economy(CountryEconomy::load(id,trigger, currency)) {
}

const std::string& Country::getName() {
    return name;
}

const std::shared_ptr<CountryEconomy>& Country::getEconomyManager() const noexcept {
    return economy;
}
}
