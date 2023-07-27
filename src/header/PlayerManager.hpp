#pragma once
#ifndef PLUGIN_PLAYER_MANAGER_H
#define PLUGIN_PLAYER_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include "PlayerMoney.hpp"
#include "api.hpp"
namespace tes {
class DLL PlayerManager {
public:
    // static PlayerManager& getInstance();

    void newPlayer(const std::string& name);

    std::shared_ptr<PlayerMoney> getPlayer(Types::player_name name);

    void addPlayer(const std::string& name, std::shared_ptr<PlayerMoney>);

    const std::unordered_map<std::string, std::shared_ptr<PlayerMoney>>& getAllPlayer();

    void saveAll();

private:
    std::unordered_map<std::string, std::shared_ptr<PlayerMoney>> players;
};
}

#endif
