#include <currency/Currency.hpp>

namespace tes {

Currency::Currency(nlohmann::json json) : currency_name(json["name"].get<std::string>()) {}

nlohmann::json Currency::get_json() {
    nlohmann::json result;
    result["name"] = this->currency_name;
    return result;
}
}
