#include <country/Country.hpp>
#include <memory>
namespace tes {
Country::Country(std::string name_,
                 country_id id_)
    : name(std::move(name_)),
      citizen(std::make_shared<CountryCitizen>()),
      id(id_) {
}

nlohmann::json Country::get_json() {
    nlohmann::json result;
    result["id"] = id;
    result["name"] = name;
    return result;
}

Country::Country(nlohmann::json data)
  : id(data["id"].get<country_id>()),
    name(data["name"].get<std::string>()) {
}
}
