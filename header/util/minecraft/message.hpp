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

inline void sendTrlText(Player *player, const Arrai18n::trl_text& trl_text) {
    if (player != nullptr) {
        player->sendText(Arrai18n::trl(player->getLanguageCode(), trl_text));
    }
}

inline std::string trl(const CommandOrigin& origin, const Arrai18n::trl_text& text) {
    if (Player* player_ptr = origin.getPlayer();
        player_ptr != nullptr) {
        return Arrai18n::trl(player_ptr->getLanguageCode(), text);
    }
    return Arrai18n::trl("", text);
}
}

#endif  // TES_MONEY_MC_UTIL_HPP
