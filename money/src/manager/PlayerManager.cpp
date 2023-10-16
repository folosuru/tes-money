#include <player/PlayerManager.hpp>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <utility>
#include <Nlohmann/json.hpp>
#include <SQLiteCpp/SQLiteCpp>
namespace tes {

    PlayerManager::PlayerManager(std::shared_ptr<CurrencyManager> m) : currency_manager_(std::move(m)) {
    }

    void PlayerManager::newPlayer(const std::string& name) {
        if (players.find(name) == players.end()) {
            players[name] = std::make_shared<PlayerMoney>();
            return;
        } else {
            throw std::invalid_argument("already exist!");
        }
    }

    std::shared_ptr<PlayerMoney> PlayerManager::getPlayer(Types::player_name_view name) {
        if (exists(name)) {
            return players[name];
        } else {
            throw std::invalid_argument("player not exists");
        }
    }

    void PlayerManager::addPlayer(const std::string& name, std::shared_ptr<PlayerMoney> player) {
        if (players.find(name) == players.end()) {
            players[name] = std::move(player);
            return;
        } else {
            throw std::invalid_argument("already exist!");
        }
    }

    const std::unordered_map<std::string, std::shared_ptr<tes::PlayerMoney>> &PlayerManager::getAllPlayer() noexcept {
        return players;
    }

    bool PlayerManager::exists(Types::player_name_view name) noexcept {
        return players.contains(name);
    }

    void PlayerManager::saveAll() {
        SQLite::Database db(file_export_path,
                            SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        SQLite::Statement query {db, "INSERT INTO money (name, currency, value) VALUES (?,?,?)"};
        SQLite::Statement query {db, "UPDATE money SET value = ? where name = ?, currency = ?"};
        for (const auto& item : players) {
            if (!item.second->edited) continue;
            for (const auto& money : item.second->getAll()) {
                // TODO: UPSERT
            }
        }
    }

    void PlayerManager::loadAll() {
        SQLite::Database db(file_export_path,
                            SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db.exec("CREATE TABLE IF NOT EXISTS money (name text, currency text, value INT);");

        SQLite::Statement   query(db, "SELECT name, currency, value FROM money");
        while (query.executeStep()) {
            // Demonstrate how to get some typed column value
            std::string player   = query.getColumn(0);
            std::string currency = query.getColumn(1);
            Types::money_value value = query.getColumn(2);
            if (!this->exists(player)) {
                this->addPlayer(std::make_shared<PlayerMoney>());
            }
            this->getPlayer(player)
                ->add(Money(value,currency_manager_->getCurrency(currency)));
        }
    }
}
