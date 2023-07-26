#pragma once
#ifndef PLUGIN_PLAYER_MANAGER_H
#define PLUGIN_PLAYER_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include "Player.hpp"
namespace tes {
class DLL PlayerManager {
public:
    // static PlayerManager& getInstance();

    void newPlayer(const std::string& name);

    std::shared_ptr<tes::Player> getPlayer(Types::player_name name);

    void addPlayer(const std::string& name, std::shared_ptr<tes::Player>);

    const std::unordered_map<std::string, std::shared_ptr<tes::Player>>& getAllPlayer();

    void saveAll();

private:
    std::unordered_map<std::string, std::shared_ptr<Player>> players;
};
}

#endif
