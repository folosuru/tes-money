#include <currency/CurrencyManager.hpp>
#include <format>
#include <algorithm>
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <SQLiteCpp/SQLiteCpp>

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

void CurrencyManager::loadAll() {
        SQLite::Database db(file_export_path,
                            SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db.exec("CREATE TABLE IF NOT EXISTS currency (name text);");

        SQLite::Statement   query(db, "SELECT name FROM currency");
        while (query.executeStep()) {
            // Demonstrate how to get some typed column value
            std::string name = query.getColumn(0);
            this->addCurrency(
                std::make_shared<Currency>(name),
                false
            );
        }
}

void CurrencyManager::save(const std::string& key) {
    SQLite::Database db(file_export_path,
                        SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    
    SQLite::Statement query1(db,
                             "INSERT INTO currency (name) VALUES (?) ON CONFLICT(name) DO NOTHING");
    query1.bind(1, name);
    query1.exec();
}

void CurrencyManager::setCommandUpdater(CurrencyCommandUpdater* upd) {
    this->updater = std::shared_ptr<CurrencyCommandUpdater>(upd);
}
}
