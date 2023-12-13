#pragma once
#ifndef TES_MONEY_MC_UTIL_HPP
#define TES_MONEY_MC_UTIL_HPP
#include <llapi/mc/Player.hpp>
#include <string>
#include <CppArrai18n/Arrai18n_def.hpp>

class Player;
namespace tes::util {
inline void sendText(Player *player, std::string text) {
    if (player != nullptr) {
        player->sendText(text);
    }
}


inline void sendText(Player *player, const Arrai18n::trl_text& text) {
    if (player != nullptr) {
        player->sendText(Arrai18n::trl(player->getLanguageCode(), text));
    }
}
}

#endif  // TES_MONEY_MC_UTIL_HPP
