#pragma once
#ifndef TES_MONEY_SRC_CURRENCY_CURRENCYCOMMANDUPDATER_HPP_
#define TES_MONEY_SRC_CURRENCY_CURRENCYCOMMANDUPDATER_HPP_
#include <llapi/DynamicCommandAPI.h>

namespace tes {
class CurrencyCommandUpdater {

 public:
    CurrencyCommandUpdater(const DynamicCommandInstance *normal_command, const DynamicCommandInstance *operator_command)
        : normal_command(normal_command), operator_command(operator_command) {}

    void updateCurrencyList(const std::vector<std::string>& new_currency_list);

 private:
    const DynamicCommandInstance *normal_command;
    const DynamicCommandInstance *operator_command;
};
}
#endif  // TES_MONEY_SRC_CURRENCY_CURRENCYCOMMANDUPDATER_HPP_
