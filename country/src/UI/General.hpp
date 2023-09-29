#pragma once
#ifndef TES_MONEY_COUNTRY_SRC_UI_GENERAL_HPP_
#define TES_MONEY_COUNTRY_SRC_UI_GENERAL_HPP_
#include <functional>
#include <string>
#include <memory>
#include "country/Country.hpp"

namespace tes::UI {
    void showCountryList(std::function<void(std::shared_ptr<Country>)> selected,std::function<void()> onClose);

    void showCountryDetail(std::function<void()>, std::string button_name);
}
#endif //TES_MONEY_COUNTRY_SRC_UI_GENERAL_HPP_
