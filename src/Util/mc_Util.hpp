#pragma once
#ifndef TES_MONEY_MC_UTIL_HPP
#define TES_MONEY_MC_UTIL_HPP

#define sendText(player, text) \
if (player != nullptr) {       \
   player->sendText(text);     \
}

#endif  // TES_MONEY_MC_UTIL_HPP
