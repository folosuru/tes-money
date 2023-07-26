
#include "../header/CurrencyManager.hpp"

namespace tes {
    std::shared_ptr<Currency> CurrencyManager::getCurrency(const std::string &str) {
        return cur[str];
    }
}
