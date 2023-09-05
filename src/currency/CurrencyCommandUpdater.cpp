#include "CurrencyCommandUpdater.hpp"
namespace tes {
void CurrencyCommandUpdater::updateCurrencyList(const std::vector<std::string>& new_currency_list) {
    this->operator_command->setSoftEnum("currency name",new_currency_list);
    this->normal_command->setSoftEnum("currency name",new_currency_list);
}
}