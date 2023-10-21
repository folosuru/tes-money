#pragma once
#ifndef PLUGIN_PLAYER_MANAGER_H
#define PLUGIN_PLAYER_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <types/GeneralTypes.hpp>
#include "PlayerMoney.hpp"
#include "../currency/CurrencyManager.hpp"
#include "Util/dll_declspec.hpp"

namespace tes {
class PlayerMoney;  // これ消すとなぜか動かない。消すな
class TES_MONEY_DLL PlayerManager {
public:
    PlayerManager() = delete;
    explicit PlayerManager(std::shared_ptr<CurrencyManager>);

    static std::shared_ptr<PlayerManager> get();

    void newPlayer(const std::string& name);

    std::shared_ptr<PlayerMoney> getPlayer(Types::player_name_view name);

    inline bool exists(Types::player_name_view name) noexcept;

    void addPlayer(const std::string& name, std::shared_ptr<PlayerMoney>);

    const std::unordered_map<std::string, std::shared_ptr<PlayerMoney>>& getAllPlayer() noexcept;

    void loadAll();
    void saveAll();

private:
    const std::string file_export_path = "plugins/tes/money/player";
    std::unordered_map<std::string, std::shared_ptr<PlayerMoney>> players;
    std::shared_ptr<CurrencyManager> currency_manager_;
};
}

#endif
