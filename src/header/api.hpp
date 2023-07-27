#pragma once
#ifndef PLUGIN_API_HPP
#define PLUGIN_API_HPP
#ifdef plugin_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif
#include <memory>
#include "PlayerManager.hpp"
class CurrencyManager;
namespace tes {

    DLL std::shared_ptr<PlayerManager> getPlayerManager();

    DLL std::shared_ptr<CurrencyManager> getCurrencyManager();

}
#endif  // PLUGIN_API_HPP
