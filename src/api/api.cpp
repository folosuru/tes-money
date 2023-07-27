#include "../header/api.hpp"

namespace tes {

    std::shared_ptr<PlayerManager> PlayerMoneyManager;
    std::shared_ptr<CurrencyManager> CurrencyManager_;

    std::shared_ptr<PlayerManager> getPlayerManager() {
        return PlayerMoneyManager;
    }

    std::shared_ptr<CurrencyManager> getCurrencyManager() {
        return CurrencyManager_;
    }
}