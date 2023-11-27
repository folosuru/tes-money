#ifndef DEBUG_WITHOUT_LLAPI
#include "JoinCountry.hpp"
#include <llapi/mc/Player.hpp>
#include <llapi/FormUI.h>

namespace tes::UI::CountryForm {

namespace {
std::string getCountryInformation(const std::string& lang, const std::shared_ptr<Country>& country) {
    return Arrai18n::trl(lang, "country.form.countryDetail");
}

void showCountryDetail(Player *pl,
                       const std::shared_ptr<Country>& country,
                       const std::shared_ptr<CitizenRefer>& refer,
                       const std::function<void()>& return_to) {
    Form::SimpleForm form(country->getName(), getCountryInformation(pl->getLanguageCode(), country));
    form.addButton(Arrai18n::trl(pl->getLanguageCode(), "country.join"), "", [country, refer](Player *pl) {
        countryJoinConfirm(pl, country, refer);
    });
    form.addButton(Arrai18n::trl(pl->getLanguageCode(), "country.form.return"), "", [return_to](Player *pl) {
        return_to();
    });
    form.sendTo(pl);
}
}

void findCountry(Player *pl, const std::shared_ptr<DataManager>& data) {
    //static_assert(false);
}

void showCountryIndex(Player *pl, const std::shared_ptr<DataManager>& data, int page) {
    Form::SimpleForm form(
        "", Arrai18n::trl(pl->getLanguageCode(), "country.form.countryIndex.description", {std::to_string(page)}));
    for (const auto& i : data->CountryManager->getAll()) {
        form.addButton(i.second->getName(), "", [i, data](Player *pl) {
            showCountryDetail(pl, i.second, data->CitizenRefer, [pl, data]() {
                showCountryIndex(pl, data);
            });
        });
    }
    form.sendTo(pl);
}

void countryJoinConfirm(Player *pl, const std::shared_ptr<Country>& country, const std::shared_ptr<CitizenRefer> ref) {
    Form::ModalForm f("",
                      Arrai18n::trl(pl->getLanguageCode(), "country.join.confirm", {country->getName()}),
                      Arrai18n::trl(pl->getLanguageCode(), "yes"),
                      Arrai18n::trl(pl->getLanguageCode(), "no"));
    f.sendTo(pl, [country, ref](Player *player, bool isConfirm) {
        if (isConfirm) {
            Citizen::build(ref, country, PlayerIdentifyProvider::get()->getIdentifyByPlayer(player));
            player->sendText(Arrai18n::trl(player->getLanguageCode(), "country.joined", {country->getName()}));
        }
    });
}

void createCountry(Player *player,
                   const std::shared_ptr<CountryManager>& mng,
                   const std::shared_ptr<PlayerIdentifyProvider>& identify_prov,
                   std::shared_ptr<CitizenRefer> ref) {
    Form::CustomForm form("");
    form.addInput("name", Arrai18n::trl(player->getLanguageCode(), "country.form.create.name"));
    form.sendTo(player, [mng, ref, identify_prov](Player *player, auto result) {
        if (result.empty()) return;
        auto country = std::make_shared<Country>(
            result["name"]->getString(),
            mng->genNextCountryId()
        );
        mng->addCountry(country);
        Citizen::build(ref, country, identify_prov->getIdentifyByPlayer(player));
    });
}

}  // namespace tes::UI::CountryForm
#endif