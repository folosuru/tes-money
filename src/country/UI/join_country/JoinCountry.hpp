#ifndef TES_SRC_COUNTRY_UI_JOIN_COUNTRY_JOINCOUNTRY_HPP_
#define TES_SRC_COUNTRY_UI_JOIN_COUNTRY_JOINCOUNTRY_HPP_
#include <functional>
#include <string>
#include <memory>
#include <llapi/mc/Player.hpp>
#include <DataManager.hpp>
#include <country/Country.hpp>

namespace tes::UI::CountryForm {
void findCountry(Player *, const std::shared_ptr<DataManager>&);

void showCountryIndex(Player *, const std::shared_ptr<DataManager>&, int page = 0);
}
#endif //TES_SRC_COUNTRY_UI_JOIN_COUNTRY_JOINCOUNTRY_HPP_
