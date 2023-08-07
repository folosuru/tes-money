#include "../header/CurrencyManager.hpp"
#include <algorithm>
#include <stdexcept>
namespace tes {

    std::shared_ptr<Currency> CurrencyManager::getCurrency(std::string str) {
        std::transform(str.begin(),str.end(),str.begin(),tolower);
        if (!cur.contains(str)){
            throw std::invalid_argument("currency not found");
        }
        return cur[str];
    }

    const std::vector<std::string>& CurrencyManager::getAllCurrencyList() {
        return currency_name_list;
    }

    void CurrencyManager::addCurrency(const std::shared_ptr<Currency>& c) {
        std::string key = c->currency_name;
        std::transform(key.begin(),key.end(),key.begin(),tolower);
        cur[key] = c;
    }

bool CurrencyManager::exists(std::string str) {
    std::transform(str.begin(),str.end(),str.begin(),tolower);
    return cur.contains(str);
}
}
