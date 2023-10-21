#pragma once
#ifndef TES_COUNTRY_SRC_COUNTRYMANAGER_DATALOADER_HPP_
#define TES_COUNTRY_SRC_COUNTRYMANAGER_DATALOADER_HPP_

#include <manager/CountryManager.hpp>
#include <manager/CitizenRefer.hpp>
#include <citizen/Citizen.hpp>
#include <utility>
#include <SQLiteCpp/SQLiteCpp.h>
#include <permission/PermissionManager.hpp>

namespace tes::Country_task {
    void loadCitizen(std::shared_ptr<CountryManager> manager,
                     std::shared_ptr<CitizenRefer> refer_,
                     std::shared_ptr<PermissionManager>);

    void loadCountry(std::shared_ptr<CountryManager> manager);

    void saveCitizen(std::shared_ptr<Citizen>);
}
#endif //TES_COUNTRY_SRC_COUNTRYMANAGER_DATALOADER_HPP_
