#pragma once
#ifndef PLUGIN_PLAYER_MANAGER_H
#define PLUGIN_PLAYER_MANAGER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <types/GeneralTypes.hpp>
#include <money/player/PlayerMoney.hpp>
#include <currency/CurrencyManager.hpp>
#include <util/player_identify/PlayerIdentify.hpp>
#include <util/dll_declspec.hpp>

namespace tes {
class PlayerMoney;  // これ消すとなぜか動かない。消すな
class TES_DLL PlayerManager {
public:
    PlayerManager() = delete;

    explicit PlayerManager(std::shared_ptr<CurrencyManager>);

    static std::shared_ptr<PlayerManager> load(const std::shared_ptr<CurrencyManager>&,
                                               const std::shared_ptr<PlayerIdentifyProvider>&);

    void newPlayer(const PlayerIdentify& name);

    std::shared_ptr<PlayerMoney> getPlayer(PlayerIdentify name);

    inline bool exists(PlayerIdentify name) noexcept;

    void addPlayer(const PlayerIdentify&, std::shared_ptr<PlayerMoney>);

    const std::unordered_map<PlayerIdentify, std::shared_ptr<PlayerMoney>>& getAllPlayer() noexcept;

    void saveAll();

private:
    static const inline std::string file_export_path = "plugins/tes/money/player";

    std::unordered_map<PlayerIdentify, std::shared_ptr<PlayerMoney>> players;

    std::shared_ptr<CurrencyManager> currency_manager_;
};
}

#endif
