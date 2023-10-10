#pragma once
#ifndef TES_MONEY_MC_UTIL_HPP
#define TES_MONEY_MC_UTIL_HPP

// 別の場所に移動させるべき。（確固たる意思）

/**
 * send text to player if player exists.
 * @param player ::Player*
 * @param text std::string
 */
#define sendTextToPlayer(player, text) if (player != nullptr) { player->sendText(text); }

#endif  // TES_MONEY_MC_UTIL_HPP
