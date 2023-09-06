#include "../header/api.hpp"

namespace tes {

    std::shared_ptr<CurrencyManager> CurrencyManager_;
    std::shared_ptr<PlayerManager> PlayerMoneyManager;

    void initCurrencyManager(CurrencyCommandUpdater updater) {
        CurrencyManager_ = std::make_shared<CurrencyManager>();
        PlayerMoneyManager = std::make_shared<PlayerManager>(CurrencyManager_);
    }

    std::shared_ptr<PlayerManager> getPlayerManager() {
        return PlayerMoneyManager;
    }

    std::shared_ptr<CurrencyManager> getCurrencyManager() {
        return CurrencyManager_;
    }
}
