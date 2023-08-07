#include "../header/PlayerManager.hpp"
#include <memory>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <utility>
#include <Nlohmann/json.hpp>

namespace tes {

    PlayerManager::PlayerManager(std::shared_ptr<CurrencyManager> m) : currency_manager_(std::move(m)) {}

    void PlayerManager::newPlayer(const std::string& name) {
        if (players.find(name) == players.end()) {
            players[name] = std::make_shared<PlayerMoney>();
            return;
        } else {
            throw std::invalid_argument("already exist!");
        }
    }

    std::shared_ptr<PlayerMoney> PlayerManager::getPlayer(Types::player_name name) {
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

    const std::unordered_map<std::string, std::shared_ptr<tes::PlayerMoney>> &PlayerManager::getAllPlayer() {
        return players;
    }

    bool PlayerManager::exists(Types::player_name_view name) {
        return players.contains(name);
    }

    void PlayerManager::saveAll() {
        for (const auto& item : players) {  // ここリファクタリングの余地
            if (!item.second->edited) continue;
            nlohmann::json data = item.second->get_json();
            std::ofstream(std::format("{}/{}.json",file_export_path,item.first)) << data << std::endl;
        }
    }

    void PlayerManager::loadAll() {
        for (const auto& entry : std::filesystem::directory_iterator(file_export_path)) {
            if (!std::filesystem::is_regular_file(entry)) continue;
            nlohmann::json j = nlohmann::json::parse(std::ifstream(entry.path()));
            std::string player_name = entry.path().stem().string();
            std::shared_ptr<tes::PlayerMoney> player_money(new PlayerMoney(j, currency_manager_));
            this->addPlayer(player_name, player_money);
        }
    }
}
