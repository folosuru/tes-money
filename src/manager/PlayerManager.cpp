#include "../header/PlayerManager.hpp"
#include <memory>
#include <stdexcept>
#include <utility>
namespace tes {

    void PlayerManager::newPlayer(const std::string& name) {
        if (players.find(name) == players.end()) {
            players[name] = std::make_shared<PlayerMoney>();
            return;
        } else {
            throw std::invalid_argument("already exist!");
        }
    }

    std::shared_ptr<PlayerMoney> PlayerManager::getPlayer(Types::player_name name) {
        if (players.find(name) != players.end()) {
            return players[name];
        } else {
            return nullptr;
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

}
