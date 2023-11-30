#ifndef TES_SRC_COUNTRY_UI_JOIN_COUNTRY_JOINCOUNTRY_HPP_
#define TES_SRC_COUNTRY_UI_JOIN_COUNTRY_JOINCOUNTRY_HPP_
#ifndef DEBUG_WITHOUT_LLAPI
#include <functional>
#include <string>
#include <memory>
#include <llapi/mc/Player.hpp>
#include <DataManager.hpp>
#include <country/Country.hpp>

namespace tes::UI::CountryForm {
void findCountry(Player *, const std::shared_ptr<DataManager>&);

void showCountryIndex(Player *, const std::shared_ptr<DataManager>&, int page = 0);

void countryJoinConfirm(Player *, const std::shared_ptr<Country>&, const std::shared_ptr<CitizenRefer>);

void createCountry(Player *player,
                   const std::shared_ptr<CountryManager>& mng,
                   const std::shared_ptr<PlayerIdentifyProvider>& identify_prov,
                   std::shared_ptr<CitizenRefer> ref,
                   const std::shared_ptr<PermissionManager>& perm);
}
#endif
#endif //TES_SRC_COUNTRY_UI_JOIN_COUNTRY_JOINCOUNTRY_HPP_
