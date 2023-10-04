#include <currency/CurrencyManager.hpp>
#include <player/PlayerManager.hpp>

namespace tes {

    std::shared_ptr<CurrencyManager> CurrencyManager_ = std::make_shared<CurrencyManager>();
    std::shared_ptr<PlayerManager> PlayerMoneyManager = std::make_shared<PlayerManager>(CurrencyManager_);

    std::shared_ptr<PlayerManager> PlayerManager::get() {
        return PlayerMoneyManager;
    }

    std::shared_ptr<CurrencyManager> CurrencyManager::get() {
        return CurrencyManager_;
    }
}
