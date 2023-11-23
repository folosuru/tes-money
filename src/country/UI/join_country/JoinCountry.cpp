#include "JoinCountry.hpp"

#include <llapi/FormUI.h>

namespace tes::UI::CountryForm {

namespace {}

void findCountry(Player *pl, const std::shared_ptr<DataManager>& data) {}

void showCountryIndex(Player *pl, const std::shared_ptr<DataManager>& data, int page) {
    Form::SimpleForm form(
        "", Arrai18n::trl(pl->getLanguageCode(), "country.form.countryIndex.description", {std::to_string(page)}));
    for (const auto& i : data->CountryManager->getAll()) {
        form.addButton(i.second->getName(), "", [](Player *pl) {

        });
    }
}

}  // namespace tes::UI::CountryForm