#include <misc/CurrencyCommandUpdater.hpp>
#include <string>
#include <vector>

namespace tes {
#ifndef DEBUG_WITHOUT_LLAPI

void CurrencyCommandUpdater::updateCurrencyList(const std::vector<std::string>& new_currency_list) {
    this->operator_command->setSoftEnum("currency name", new_currency_list);
    this->normal_command->setSoftEnum("currency name", new_currency_list);
}

#else
void CurrencyCommandUpdater::updateCurrencyList(const std::vector<std::string>& new_currency_list) {
    return;
}
#endif
}
