#include <currency/CurrencyManager.hpp>
#include <format>
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <CppArrai18n/Arrai18n_def.hpp>

namespace tes {

std::shared_ptr<Currency> CurrencyManager::getCurrency(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    return cur.at(str);
}

const std::vector<std::string>& CurrencyManager::getAllCurrencyList() {
    return currency_name_list;
}

void CurrencyManager::addCurrency(const std::shared_ptr<Currency>& c, bool updateCommand) {
    std::string key = c->currency_name;
    std::transform(key.begin(), key.end(), key.begin(), tolower);
    cur[key] = c;
    if (updateCommand && updater) {
        this->updater->updateCurrencyList(getAllCurrencyList());
    }
}

bool CurrencyManager::exists(std::string str) const noexcept {
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    return cur.contains(str);
}

void CurrencyManager::save(const std::string& key) {
    std::filesystem::create_directories(file_export_path);
    nlohmann::json j = cur.at(key)->get_json();
    std::ofstream(std::format("{}/{}.json", file_export_path, cur.at(key)->currency_name)) << j << std::endl;
}

CurrencyManager::CurrencyManager() = default;

void CurrencyManager::setCommandUpdater(CurrencyCommandUpdater *upd) {
    this->updater = std::shared_ptr<CurrencyCommandUpdater>(upd);
}

util::OptionalMessage<void,
                      Arrai18n::trl_text> CurrencyManager::currencyNameValidation(const std::string& name) const noexcept {
    typedef tes::util::OptionalMessage<void, Arrai18n::trl_text> return_type;
    if (name.empty()) return return_type({"money.currency.validation.fail.empty", {}});
    if (exists(name)) return return_type({"money.currency.validation.fail.already_exist", {name}});
    return return_type();
}

std::shared_ptr<CurrencyManager> CurrencyManager::load() {
    auto result = std::make_shared<CurrencyManager>();

    std::filesystem::create_directories(CurrencyManager::file_export_path);
    for (const auto& entry : std::filesystem::directory_iterator(file_export_path)) {
        if (!std::filesystem::is_regular_file(entry)) continue;
        nlohmann::json j = nlohmann::json::parse(std::ifstream(entry.path()));
        result->addCurrency(std::make_shared<Currency>(j), false);
    }
    if (result->updater) {
        result->updater->updateCurrencyList(result->getAllCurrencyList());
    }
    return result;
}
}
