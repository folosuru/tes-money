#pragma once
#ifndef TES_MONEY_MC_UTIL_HPP
#define TES_MONEY_MC_UTIL_HPP
#include <llapi/mc/Player.hpp>
#include <string>

class Player;
namespace tes::util {
inline void sendText(Player *player, std::string text) {
    if (player != nullptr) {
        player->sendText(text);
    }
}
}

#endif  // TES_MONEY_MC_UTIL_HPP
