#pragma once
#ifndef PLUGIN_CURRENCYMANAGER_HPP
#define PLUGIN_CURRENCYMANAGER_HPP
#include <memory>
#include <unordered_map>
#include <string>
#include "Currency.hpp"
#include "api.hpp"

namespace tes {
class DLL CurrencyManager {
public:
    std::shared_ptr<Currency> getCurrency(const std::string& str);

private:
    std::unordered_map<std::string, std::shared_ptr<Currency>> cur;
};
}  // tes

#endif  // PLUGIN_CURRENCYMANAGER_HPP
