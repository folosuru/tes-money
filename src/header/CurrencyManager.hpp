#pragma once
#ifndef PLUGIN_CURRENCYMANAGER_HPP
#define PLUGIN_CURRENCYMANAGER_HPP
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "Currency.hpp"
#include "../Util/dll_declspec.hpp"

namespace tes {
class TES_MONEY_DLL CurrencyManager {
public:
    CurrencyManager() = default;
    std::shared_ptr<Currency> getCurrency(std::string str);

    void addCurrency(const std::shared_ptr<Currency>& c);

    bool exists(std::string str);

    const std::vector<std::string>& getAllCurrencyList();

    void loadAll();
    void save(const std::string& key);

private:
    const std::string file_export_path = "plugins/tes/money/currency";
    std::unordered_map<std::string, std::shared_ptr<Currency>> cur;
    std::vector<std::string> currency_name_list;
};
}  // tes

#endif  // PLUGIN_CURRENCYMANAGER_HPP
