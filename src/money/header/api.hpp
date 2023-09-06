#pragma once
#ifndef PLUGIN_API_HPP
#define PLUGIN_API_HPP
#include <memory>
#include "PlayerManager.hpp"
#include "CurrencyManager.hpp"
#include "../Util/dll_declspec.hpp"

namespace tes {
class PlayerManager;
class CurrencyManager;
class CurrencyCommandUpdater;

    void initCurrencyManager(CurrencyCommandUpdater);

    TES_MONEY_DLL std::shared_ptr<PlayerManager> getPlayerManager();

    TES_MONEY_DLL std::shared_ptr<CurrencyManager> getCurrencyManager();

}
#endif  // PLUGIN_API_HPP
