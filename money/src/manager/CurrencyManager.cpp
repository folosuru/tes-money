#include <currency/CurrencyManager.hpp>
#include <format>
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <utility>

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

bool CurrencyManager::exists(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    return cur.contains(str);
}

void CurrencyManager::loadAll() {
    std::filesystem::create_directories(this->file_export_path);
    for (const auto& entry : std::filesystem::directory_iterator(file_export_path)) {
        if (!std::filesystem::is_regular_file(entry)) continue;
        nlohmann::json j = nlohmann::json::parse(std::ifstream(entry.path()));
        this->addCurrency(std::make_shared<Currency>(j), false);
    }
    if (this->updater) {
        this->updater->updateCurrencyList(getAllCurrencyList());
    }
}

void CurrencyManager::save(const std::string& key) {
    std::filesystem::create_directories(file_export_path);
    nlohmann::json j = cur.at(key)->get_json();
    std::ofstream(std::format("{}/{}.json", file_export_path, cur.at(key)->currency_name)) << j << std::endl;
}

CurrencyManager::CurrencyManager() {
    loadAll();
}

void CurrencyManager::setCommandUpdater(CurrencyCommandUpdater* upd) {
    this->updater = std::shared_ptr<CurrencyCommandUpdater>(upd);
}
}
