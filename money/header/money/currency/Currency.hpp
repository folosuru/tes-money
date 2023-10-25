#pragma once
#ifndef PLUGIN_CURRENCY_HPP
#define PLUGIN_CURRENCY_HPP
#include <string>
#include <utility>
#include "Util/dll_declspec.hpp"

namespace tes {
class TES_MONEY_DLL Currency {
public:
    explicit Currency(std::string name) noexcept : currency_name(std::move(name)) {}

    const std::string currency_name;

    Currency() = delete;
    Currency & operator = ( const Currency & ) = delete;
    Currency( const Currency & ) = delete;
};
}  // tes
#endif  // PLUGIN_CURRENCY_HPP
