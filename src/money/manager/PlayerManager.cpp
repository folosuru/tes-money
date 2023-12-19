#include <money/player/PlayerManager.hpp>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <utility>
#include <format>
#include <util/player_identify/PlayerIdentifyProvider.hpp>
#include <Nlohmann/json.hpp>

namespace tes {

PlayerManager::PlayerManager(std::shared_ptr<CurrencyManager> m) : currency_manager_(std::move(m)) {
}

void PlayerManager::newPlayer(const PlayerIdentify& player) {
    if (players.find(player) == players.end()) {
        players.insert({player, std::make_shared<PlayerMoney>(player)});
        return;
    } else {
        throw std::invalid_argument("already exist!");
    }
}

std::shared_ptr<PlayerMoney> PlayerManager::getPlayer(PlayerIdentify name) {
    if (auto target = players.find(name);
        target != players.end()) {
        return target->second;
    } else {
        throw std::invalid_argument("player not exists");
    }
}

void PlayerManager::addPlayer(const PlayerIdentify& name, std::shared_ptr<PlayerMoney> player) {
    if (players.find(name) == players.end()) {
        players.insert({name, std::move(player)});
        return;
    } else {
        throw std::invalid_argument("already exist!");
    }
}

const std::unordered_map<PlayerIdentify, std::shared_ptr<tes::PlayerMoney>>& PlayerManager::getAllPlayer() noexcept {
    return players;
}

bool PlayerManager::exists(PlayerIdentify name) noexcept {
    return players.contains(name);
}

void PlayerManager::saveAll() {
    std::filesystem::create_directories(file_export_path);
    for (const auto& item : players) {  // ここリファクタリングの余地
        if (!item.second->edited) continue;
        nlohmann::json data = item.second->get_json();
        data["name"] = item.first->name;
        std::ofstream(std::format("{0}/{1}.json", file_export_path, item.first->name)) << data << std::endl;
    }
}

std::shared_ptr<PlayerManager> PlayerManager::load(const std::shared_ptr<CurrencyManager>& manager,
                                                   const std::shared_ptr<PlayerIdentifyProvider>& identify) {
    auto result = std::make_shared<PlayerManager>(manager);
    std::filesystem::create_directories(file_export_path);
    for (const auto& entry : std::filesystem::directory_iterator(file_export_path)) {
        if (!std::filesystem::is_regular_file(entry)) continue;
        nlohmann::json j = nlohmann::json::parse(std::ifstream(entry.path()));
        PlayerIdentify player_identify = identify->getIdentify(j["name"].get<std::string>());
        std::shared_ptr<tes::PlayerMoney> player_money(PlayerMoney::init(j, manager, player_identify));
        result->addPlayer(player_identify, player_money);
    }
    return result;
}

}
