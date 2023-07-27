#pragma once
#ifndef PLUGIN_TYPES_HPP
#define PLUGIN_TYPES_HPP
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "../header/Currency.hpp"


namespace tes::Types {
    // typedef std::string currency;
    typedef std::shared_ptr<Currency> currency;
    typedef std::string player_name;
    typedef const std::string& player_name_view;
    typedef std::vector<std::string> player_list;
    typedef std::pair<int, int> posXZ;
    typedef int country;
    typedef int money_value;
}
#endif  // PLUGIN_TYPES_HPP
